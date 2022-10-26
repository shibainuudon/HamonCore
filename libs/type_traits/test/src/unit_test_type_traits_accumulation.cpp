/**
 *	@file	unit_test_type_traits_accumulation.cpp
 *
 *	@brief	accumulation のテスト
 */

#include <hamon/type_traits/accumulation.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon_type_traits_test
{

namespace accumulation_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_ACCUMULATION_TEST(x, ...)	\
	static_assert(hamon::accumulation_v<__VA_ARGS__>      == x, "");	\
	static_assert(hamon::accumulation<__VA_ARGS__>::value == x, "");	\
	static_assert(hamon::accumulation<__VA_ARGS__>()      == x, "")

#else

#define HAMON_ACCUMULATION_TEST(x, ...)	\
	static_assert(hamon::accumulation<__VA_ARGS__>::value == x, "");	\
	static_assert(hamon::accumulation<__VA_ARGS__>()      == x, "")

#endif

using Zero  = std::integral_constant<int, 0>;
using One   = std::integral_constant<int, 1>;
using Two   = std::integral_constant<int, 2>;
using Three = std::integral_constant<int, 3>;

struct Four
{
	using value_type = signed char;
	static constexpr value_type value = 4;
	constexpr operator value_type() const noexcept { return value; }
};

struct Five
{
	using value_type = unsigned short;
	static constexpr value_type value = 5;
	constexpr operator value_type() const noexcept { return value; }
};

HAMON_ACCUMULATION_TEST(0, /**/);

HAMON_ACCUMULATION_TEST(0, Zero);
HAMON_ACCUMULATION_TEST(1, One);
HAMON_ACCUMULATION_TEST(2, Two);
HAMON_ACCUMULATION_TEST(3, Three);
HAMON_ACCUMULATION_TEST(4, Four);
HAMON_ACCUMULATION_TEST(5, Five);

HAMON_ACCUMULATION_TEST(1, One, Zero);
HAMON_ACCUMULATION_TEST(2, One, One);
HAMON_ACCUMULATION_TEST(3, One, Two);
HAMON_ACCUMULATION_TEST(4, One, Three);
HAMON_ACCUMULATION_TEST(5, One, Four);
HAMON_ACCUMULATION_TEST(6, One, Five);
HAMON_ACCUMULATION_TEST(2, Two, Zero);
HAMON_ACCUMULATION_TEST(3, Two, One);
HAMON_ACCUMULATION_TEST(4, Two, Two);
HAMON_ACCUMULATION_TEST(5, Two, Three);
HAMON_ACCUMULATION_TEST(6, Two, Four);
HAMON_ACCUMULATION_TEST(7, Two, Five);

HAMON_ACCUMULATION_TEST(6, One, Two, Three);
HAMON_ACCUMULATION_TEST(10, One, Two, Three, Four);
HAMON_ACCUMULATION_TEST(15, One, Two, Three, Four, Five);

#undef HAMON_ACCUMULATION_TEST

}	// namespace accumulation_test

}	// namespace hamon_type_traits_test
