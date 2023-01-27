/**
 *	@file	unit_test_type_traits_is_corresponding_member.cpp
 *
 *	@brief	is_corresponding_member のテスト
 */

#include <hamon/type_traits/is_corresponding_member.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_IS_CORRESPONDING_MEMBER)

namespace hamon_type_traits_test
{
namespace is_corresponding_member_test
{

struct A { int a; };
struct B { int b; };
struct C : public A, public B { };  // not a standard-layout class

static_assert(hamon::is_corresponding_member(&A::a, &B::b), "");
static_assert(hamon::is_corresponding_member<A, B>(&A::a, &B::b), "");

static_assert(hamon::is_corresponding_member(&C::a, &C::b), "");
// Succeeds because arguments have types int A::* and int B::*

constexpr int C::* a = &C::a;
constexpr int C::* b = &C::b;
static_assert(!hamon::is_corresponding_member(a, b), "");
// Not corresponding members, because arguments both have type int C::*

static_assert(noexcept(!hamon::is_corresponding_member(a, b)), "");

}	// namespace is_corresponding_member_test
}	// namespace hamon_type_traits_test

#else
#pragma message("hamon doesn't have is_corresponding_member")
#endif
