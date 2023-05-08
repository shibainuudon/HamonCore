/**
 *	@file	unit_test_type_traits_reference_converts_from_temporary.cpp
 *
 *	@brief	reference_converts_from_temporary のテスト
 */

#include <hamon/type_traits/reference_converts_from_temporary.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_REFERENCE_CONVERTS_FROM_TEMPORARY)

namespace hamon_type_traits_test
{

namespace reference_converts_from_temporary_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(b, T, U)	\
	static_assert(hamon::reference_converts_from_temporary_v<T, U>      == b, #T ", " #U);	\
	static_assert(hamon::reference_converts_from_temporary<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::reference_converts_from_temporary<T, U>{}()    == b, #T ", " #U);	\
	static_assert(hamon::reference_converts_from_temporary<T, U>{}      == b, #T ", " #U)

#else

#define HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(b, T, U)	\
	static_assert(hamon::reference_converts_from_temporary<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::reference_converts_from_temporary<T, U>{}()    == b, #T ", " #U);	\
	static_assert(hamon::reference_converts_from_temporary<T, U>{}      == b, #T ", " #U)

#endif

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, int volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, int volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int volatile&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int volatile&&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const volatile&, long const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const volatile&&, long const volatile&&);

struct A
{
	A() = default;
	A(int) {}
};

struct B : A
{
	explicit B(int) {}
	operator int();
	explicit operator int&&();
};

struct C
{
	operator struct A() { return A{}; }
	explicit operator struct B() { return B{0}; }
};

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, B const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, B const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, C const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A volatile&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A volatile&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, A const volatile&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  A const volatile&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B volatile&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int const);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int const&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int const&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int volatile&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int const volatile);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int const volatile&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, B const volatile&&, int const volatile&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int&&, B&&);

HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(false, int const, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&, B&&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, B);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, B&);
HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST(true,  int const&&, B&&);

#undef HAMON_REFERENCE_CONVERTS_FROM_TEMPORARY_TEST

}	// namespace reference_converts_from_temporary_test

}	// namespace hamon_type_traits_test

#else
#pragma message("hamon doesn't have reference_converts_from_temporary")
#endif
