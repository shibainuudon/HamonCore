/**
 *	@file	unit_test_type_traits_is_layout_compatible.cpp
 *
 *	@brief	is_layout_compatible のテスト
 */

#include <hamon/type_traits/is_layout_compatible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_IS_LAYOUT_COMPATIBLE)

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_LAYOUT_COMPATIBLE_TEST(b, T, U)	\
	static_assert(hamon::is_layout_compatible_v<T, U>      == b, #T ", " #U);	\
	static_assert(hamon::is_layout_compatible<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::is_layout_compatible<T, U>()      == b, #T ", " #U)

#else

#define HAMON_IS_LAYOUT_COMPATIBLE_TEST(b, T, U)	\
	static_assert(hamon::is_layout_compatible<T, U>::value == b, #T ", " #U);	\
	static_assert(hamon::is_layout_compatible<T, U>()      == b, #T ", " #U)

#endif

namespace hamon_type_traits_test
{
namespace is_layout_compatible_test
{

struct X { int a; };
struct Y { int b; };
struct Z { char c; };

enum class E0 : int { A, B, C };
enum class E1 : int { X, Y, Z };
enum class E2 : char { A, B, C };

HAMON_IS_LAYOUT_COMPATIBLE_TEST(true,  X, X);
HAMON_IS_LAYOUT_COMPATIBLE_TEST(true,  X, Y);
HAMON_IS_LAYOUT_COMPATIBLE_TEST(false, X, Z);
HAMON_IS_LAYOUT_COMPATIBLE_TEST(true,  E0, E1);
HAMON_IS_LAYOUT_COMPATIBLE_TEST(false, E0, E2);

}	// namespace is_layout_compatible_test
}	// namespace hamon_type_traits_test

#undef HAMON_IS_LAYOUT_COMPATIBLE_TEST

#else
#pragma message("hamon doesn't have is_layout_compatible")
#endif
