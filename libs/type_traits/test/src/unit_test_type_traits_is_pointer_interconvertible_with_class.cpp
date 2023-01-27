/**
 *	@file	unit_test_type_traits_is_pointer_interconvertible_with_class.cpp
 *
 *	@brief	is_pointer_interconvertible_with_class のテスト
 */

#include <hamon/type_traits/is_pointer_interconvertible_with_class.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS)

namespace hamon_type_traits_test
{
namespace is_pointer_interconvertible_with_class_test
{

struct A { int i; long l; };

static_assert( hamon::is_pointer_interconvertible_with_class(&A::i), "");
static_assert(!hamon::is_pointer_interconvertible_with_class(&A::l), "");

constexpr int A::* a = nullptr;
static_assert(!hamon::is_pointer_interconvertible_with_class(a), "");
static_assert(noexcept(hamon::is_pointer_interconvertible_with_class(a)), "");

struct B { const int i; };
static_assert(hamon::is_pointer_interconvertible_with_class(&B::i), "");

struct C { int f(); };
static_assert(!hamon::is_pointer_interconvertible_with_class(&C::f), "");

struct D : A { };
static_assert(hamon::is_pointer_interconvertible_with_class(&D::i), "");

struct E : A { int j; };
// This works because the type of &E::i is int A::* and A is standard-layout:
static_assert(hamon::is_pointer_interconvertible_with_class(&E::i), "");
constexpr int E::* e = a;
// This fails because E is not standard-layout:
static_assert(!hamon::is_pointer_interconvertible_with_class(e), "");
static_assert(!hamon::is_pointer_interconvertible_with_class(&E::j), "");

}	// namespace is_pointer_interconvertible_with_class_test
}	// namespace hamon_type_traits_test

#else
#pragma message("hamon doesn't have is_pointer_interconvertible_with_class")
#endif
