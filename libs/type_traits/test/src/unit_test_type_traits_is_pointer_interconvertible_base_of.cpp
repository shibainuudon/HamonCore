/**
 *	@file	unit_test_type_traits_is_pointer_interconvertible_base_of.cpp
 *
 *	@brief	is_pointer_interconvertible_base_of のテスト
 */

#include <hamon/type_traits/is_pointer_interconvertible_base_of.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_IS_POINTER_INTERCONVERTIBLE_BASE_OF)

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL(b, T, U)	\
	static_assert(hamon::is_pointer_interconvertible_base_of_v<T, U>      == b, #T ", " #U);	\
	static_assert(hamon::is_pointer_interconvertible_base_of<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::is_pointer_interconvertible_base_of<T, U>()      == b, #T ", " #U)

#else

#define HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL(b, T, U)	\
	static_assert(hamon::is_pointer_interconvertible_base_of<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::is_pointer_interconvertible_base_of<T, U>()      == b, #T ", " #U)

#endif

#define HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_CV(b, T, U)	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL(b, T,                U);	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL(b, T, const          U);	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL(b, T,       volatile U);	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL(b, T, const volatile U)

#define HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(b, T, U)	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_CV(b,                T, U);	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_CV(b, const          T, U);	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_CV(b,       volatile T, U);	\
	HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_CV(b, const volatile T, U)

namespace hamon_type_traits_test
{
namespace is_pointer_interconvertible_base_of_test
{

struct B {};
struct D : B { int i; };

HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(true,  B, B);
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(true,  B, D);
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(false, D, B);
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(true,  D, D);

struct E : D { };
// E is not standard-layout
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(false, E, B);

struct D1 : B { };
struct D2 : B { };
struct D3 : D1, D2 { };
// B is ambiguously derived
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(false, B, D3);

union U;
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(false, U, U);
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(false, U, D);

struct I; // incomplete
HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST(true,  I, I);

}	// namespace is_pointer_interconvertible_base_of_test
}	// namespace hamon_type_traits_test

#undef HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_IMPL
#undef HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST_CV
#undef HAMON_IS_POINTER_INTERCONVERTIBLE_BASE_OF_TEST

#else
#pragma message("hamon doesn't have is_pointer_interconvertible_base_of")
#endif
