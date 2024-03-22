/**
 *	@file	unit_test_iterator_concepts_indirect_equivalence_relation.cpp
 *
 *	@brief	indirect_equivalence_relation のテスト
 */

#include <hamon/iterator/concepts/indirect_equivalence_relation.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == hamon::indirect_equivalence_relation<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirect_equivalence_relation_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == hamon::indirect_equivalence_relation<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirect_equivalence_relation_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirect_equivalence_relation_test
{

struct Pred1
{
	bool operator()(int, int) const;
};
struct Pred2
{
	bool operator()(int) const;
	void operator()(int, int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int, int) const;
};

HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(true,  bool(*)(int, int), int*, int*);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(false, bool(*)(int, int), int, int);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(false, void(*)(int, int), int*, int*);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(false, void(*)(int, int), int, int);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(true,  bool(*)(int, int), short*, char*);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(true,  Pred1, int*, int*);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(false, Pred2, int*, int*);
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(false, Pred3, int*, int*);

// P2609R3

struct MoveOnly
{
	MoveOnly(MoveOnly&&) = default;
	MoveOnly(MoveOnly const&) = delete;
};
struct Proj
{
	MoveOnly operator()(int) const;
};
struct Pred4
{
	bool operator()(MoveOnly, MoveOnly) const;
};
HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST(true, Pred4, hamon::projected<int*, Proj>, hamon::projected<int*, Proj>);

}	// namespace indirect_equivalence_relation_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECT_EQUIVALENCE_RELATION_TEST
