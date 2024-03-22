/**
 *	@file	unit_test_iterator_concepts_indirect_binary_predicate.cpp
 *
 *	@brief	indirect_binary_predicate のテスト
 */

#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <memory>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECT_BINARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == hamon::indirect_binary_predicate<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirect_binary_predicate_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECT_BINARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == hamon::indirect_binary_predicate<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirect_binary_predicate_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirect_binary_predicate_test
{

struct Pred1
{
	bool operator()(int, int) const;
};
struct Pred2
{
	bool operator()(int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int, int) const;
};
struct X
{
	using value_type = int;
	int const& operator*() const;
};
struct Y
{
	//using value_type = int;
	int const& operator*() const;
};
struct Z
{
	using value_type = int;
	//int const& operator*() const;
};

HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int      *, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int const*, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int      *, int const*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int const*, int const*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, float*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, char*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int&);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int&&);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int[]);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, int[2]);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, int*, void*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, std::unique_ptr<int>);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, int*, std::shared_ptr<int>);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, hamon::vector<int>::iterator,       int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, hamon::vector<int>::iterator,       hamon::vector<int>::iterator);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, hamon::vector<int>::iterator,       hamon::vector<int>::const_iterator);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, hamon::vector<int>::const_iterator, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, hamon::vector<int>::const_iterator, hamon::vector<int>::iterator);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, hamon::vector<int>::const_iterator, hamon::vector<int>::const_iterator);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, X, X);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true,  Pred1, X, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Y, Y);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Y, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Z, Z);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred1, Z, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred2, int*, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred2, hamon::vector<int>::iterator, hamon::vector<int>::iterator);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred2, X, X);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred3, int*, int*);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred3, hamon::vector<int>::iterator, hamon::vector<int>::iterator);
HAMON_INDIRECT_BINARY_PREDICATE_TEST(false, Pred3, X, X);

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
HAMON_INDIRECT_BINARY_PREDICATE_TEST(true, Pred4, hamon::projected<int*, Proj>, hamon::projected<int*, Proj>);

}	// namespace indirect_binary_predicate_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECT_BINARY_PREDICATE_TEST
