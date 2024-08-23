/**
 *	@file	unit_test_iterator_concepts_indirect_unary_predicate.cpp
 *
 *	@brief	indirect_unary_predicate のテスト
 */

#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/memory.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECT_UNARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == hamon::indirect_unary_predicate<__VA_ARGS__>, " ");	\
	static_assert(B == hamon::indirect_unary_predicate_t<__VA_ARGS__>::value, " ")
#else
#  define HAMON_INDIRECT_UNARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == hamon::indirect_unary_predicate<__VA_ARGS__>::value, " ");	\
	static_assert(B == hamon::indirect_unary_predicate_t<__VA_ARGS__>::value, " ")
#endif

namespace hamon_iterator_test
{

namespace indirect_unary_predicate_test
{

struct Pred1
{
	bool operator()(int) const;
};
struct Pred2
{
	bool operator()(int, int) const;
	void operator()(int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int) const;
};

HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int      *      );
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int const*      );
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int      * const);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int const* const);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), float*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), char*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), void*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int**);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int const);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int&);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int&&);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int const&);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int const&&);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int[]);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int[3]);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), hamon::unique_ptr<int>);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), std::shared_ptr<int>);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), hamon::vector<int>::iterator);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), hamon::vector<int>::const_iterator);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, void(*)(int), int*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(), int*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int, int), int*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true,  Pred1, int*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, Pred2, int*);
HAMON_INDIRECT_UNARY_PREDICATE_TEST(false, Pred3, int*);

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
	bool operator()(MoveOnly) const;
};
HAMON_INDIRECT_UNARY_PREDICATE_TEST(true, Pred4, hamon::projected<int*, Proj>);

}	// namespace indirect_unary_predicate_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECT_UNARY_PREDICATE_TEST
