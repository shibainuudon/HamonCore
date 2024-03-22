/**
 *	@file	unit_test_iterator_concepts_indirectly_unary_invocable.cpp
 *
 *	@brief	indirectly_unary_invocable のテスト
 */

#include <hamon/iterator/concepts/indirectly_unary_invocable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_unary_invocable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::indirectly_unary_invocable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(B, ...)	\
	static_assert(B == hamon::indirectly_unary_invocable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::indirectly_unary_invocable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_iterator_test
{

namespace indirectly_unary_invocable_test
{

struct Pred1
{
	bool operator()(int) const;
};
struct Pred2
{
	void operator()(int const&) const;
};
struct Pred3
{
	bool operator()(int, int) const;
	bool operator()() const;
};
struct Pred4
{
	bool operator()(int&) const;
};

HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred1, int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred1, int const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred2, int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred2, int const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred3, int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred3, int const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred4, int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred4, int const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred1, short*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  Pred2, short*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred3, short*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred1, void*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred2, void*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, Pred3, void*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int, int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(int), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(int,int), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(*)(), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  int(*)(int), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(*)(int,int), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(&)(), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  int(&)(int), int*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, int(&)(int, int), int*);

struct A;
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  int A::*, A*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  int A::*, A const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  void (A::*)(),           A*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  void (A::*)() const,     A*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, void (A::*)(long),       A*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, void (A::*)(long) const, A*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, void (A::*)(),           A const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true,  void (A::*)() const,     A const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, void (A::*)(long),       A const*);
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(false, void (A::*)(long) const, A const*);

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
struct Pred5
{
	bool operator()(MoveOnly) const;
};
HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST(true, Pred5, hamon::projected<int*, Proj>);

}	// namespace indirectly_unary_invocable_test

}	// namespace hamon_iterator_test

#undef HAMON_INDIRECTLY_UNARY_INVOCABLE_TEST
