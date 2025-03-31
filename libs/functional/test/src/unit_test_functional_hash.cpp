/**
 *	@file	unit_test_functional_hash.cpp
 *
 *	@brief	hash のテスト
 */

#include <hamon/functional/hash.hpp>
#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/concepts/detail/cpp17_default_constructible.hpp>
#include <hamon/concepts/detail/cpp17_copy_assignable.hpp>
#include <hamon/concepts/detail/cpp17_swappable.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

namespace hamon_functional_test
{

namespace hash_test
{

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ   HAMON_CXX11_CONSTEXPR_EXPECT_EQ
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE   HAMON_CXX11_CONSTEXPR_EXPECT_NE
#else
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ   EXPECT_EQ
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE   EXPECT_NE
#endif

template <typename T>
void enabled_hash_test(void)
{
	static_assert(hamon::detail::cpp17_hash_t<hamon::hash<T>, T>::value, "");
	static_assert(hamon::detail::cpp17_default_constructible_t<hamon::hash<T>>::value, "");
	static_assert(hamon::detail::cpp17_copy_assignable_t<hamon::hash<T>>::value, "");
//	static_assert(hamon::detail::cpp17_swappable_t<hamon::hash<T>>::value, "");	// TODO
	static_assert(hamon::is_nothrow_invocable<hamon::hash<T>, T>::value, "");
}

template <typename T>
void disabled_hash_test(void)
{
	// [unord.hash]/4
	static_assert(!hamon::is_default_constructible<hamon::hash<T>>::value, "");
	static_assert(!hamon::is_copy_constructible<hamon::hash<T>>::value, "");
	static_assert(!hamon::is_move_constructible<hamon::hash<T>>::value, "");
	static_assert(!hamon::is_copy_assignable<hamon::hash<T>>::value, "");
	static_assert(!hamon::is_move_assignable<hamon::hash<T>>::value, "");
	static_assert(!hamon::detail::cpp17_hash_t<hamon::hash<T>, T>::value, "");
}

void bool_test(void)
{
	enabled_hash_test<bool>();

	HAMON_CXX11_CONSTEXPR auto h = hamon::hash<bool>{};

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(true),  h(true));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(true),  h(false));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(false), h(true));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(false), h(false));
}

template <typename T>
void integral_test(void)
{
	enabled_hash_test<T>();

	HAMON_CXX11_CONSTEXPR T const max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR T const min = hamon::numeric_limits<T>::min();

	HAMON_CXX11_CONSTEXPR auto h = hamon::hash<T>{};

	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(T(0)), h(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(T(0)), h(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(T(0)), h(T( 1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(max), h(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(max), h(static_cast<T>(max - 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(min), h(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(min), h(static_cast<T>(min + 1)));

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4333)
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(max), h(static_cast<T>(max >> 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(max), h(static_cast<T>(max >> 16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(max), h(static_cast<T>(max >> 31)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(max), h(static_cast<T>((max >> 16) >> 16)));
HAMON_WARNING_POP()

	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>();
		auto const b = get_random_value<T>();
		if (a == b)
		{
			EXPECT_EQ(h(a), h(b));
		}
		else
		{
			EXPECT_NE(h(a), h(b));
		}
		EXPECT_EQ(h(a), h(a));
		EXPECT_EQ(h(b), h(b));
		EXPECT_NE(h(a), h(a + T(1)));
		EXPECT_NE(h(a), h(a - T(1)));
		EXPECT_NE(h(b), h(b + T(1)));
		EXPECT_NE(h(b), h(b - T(1)));
	}
}

template <typename T>
void float_test(void)
{
	enabled_hash_test<T>();

	HAMON_CXX11_CONSTEXPR T const eps = hamon::numeric_limits<T>::epsilon();
	HAMON_CXX11_CONSTEXPR T const max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR T const min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR T const low = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR T const inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR T const nan = hamon::numeric_limits<T>::quiet_NaN();

	HAMON_CXX11_CONSTEXPR auto h = hamon::hash<T>{};

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T(+0.0)), h(T(+0.0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T(+0.0)), h(T(-0.0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T(-0.0)), h(T(+0.0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T(-0.0)), h(T(-0.0)));

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T(-1)), h(T(-1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T(-1)), h(T( 0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T(-1)), h(T( 1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T( 0)), h(T(-1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T( 0)), h(T( 0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T( 0)), h(T( 1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T( 1)), h(T(-1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T( 1)), h(T( 0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(T( 1)), h(T( 1)));

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T(0)), h(T(0) + eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T(0)), h(T(0) - eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T(1)), h(T(1) + eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(T(1)), h(T(1) - eps));

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(eps), h(eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(max), h(max));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(min), h(min));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(low), h(low));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(inf), h( inf));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(h(inf), h(-inf));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(h(nan), h(nan));

	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>(T(-1), T(1));
		auto const b = get_random_value<T>(T(-1), T(1));
		if (a == b)
		{
			EXPECT_EQ(h(a), h(b));
		}
		else
		{
			EXPECT_NE(h(a), h(b));
		}
		EXPECT_EQ(h(a), h(a));
		EXPECT_EQ(h(b), h(b));
		EXPECT_NE(h(a), h(-a));
		EXPECT_NE(h(b), h(-b));
	}
}

template <typename T>
void pointer_test(void)
{
	enabled_hash_test<T*>();
	enabled_hash_test<T const*>();
	enabled_hash_test<hamon::nullptr_t>();

	T x{};
	T y{};
	T* p1 = &x;
	T* p2 = &y;
	T* p3{};

	auto h = hamon::hash<T*>{};
	auto h2 = hamon::hash<hamon::nullptr_t>{};

	EXPECT_EQ(h(p1), h(p1));
	EXPECT_NE(h(p1), h(p2));
	EXPECT_NE(h(p1), h(p3));
	EXPECT_NE(h(p1), h2(nullptr));
	EXPECT_NE(h(p2), h(p1));
	EXPECT_EQ(h(p2), h(p2));
	EXPECT_NE(h(p2), h(p3));
	EXPECT_NE(h(p2), h2(nullptr));
	EXPECT_NE(h(p3), h(p1));
	EXPECT_NE(h(p3), h(p2));
	EXPECT_EQ(h(p3), h(p3));
	EXPECT_EQ(h(p3), h2(nullptr));
	EXPECT_NE(h2(nullptr), h(p1));
	EXPECT_NE(h2(nullptr), h(p2));
	EXPECT_EQ(h2(nullptr), h(p3));
	EXPECT_EQ(h2(nullptr), h2(nullptr));
}

inline void enum_test(void)
{
	enum Enum1
	{
		Value1_1 = 0,
		Value1_2 = 10,
		Value1_3 = 13
	};

	enabled_hash_test<Enum1>();
	{
		HAMON_CXX11_CONSTEXPR auto h = hamon::hash<Enum1>{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Value1_1), h(Value1_1));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Value1_1), h(Value1_2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Value1_1), h(Value1_3));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Value1_2), h(Value1_1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Value1_2), h(Value1_2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Value1_2), h(Value1_3));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Value1_3), h(Value1_1));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Value1_3), h(Value1_2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Value1_3), h(Value1_3));
	}

	enum class Enum2 : char
	{
		Value1, Value2, Value3, Value4
	};

	enabled_hash_test<Enum2>();
	{
		HAMON_CXX11_CONSTEXPR auto h = hamon::hash<Enum2>{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Enum2::Value1), h(Enum2::Value1));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value1), h(Enum2::Value2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value1), h(Enum2::Value3));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value1), h(Enum2::Value4));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value2), h(Enum2::Value1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Enum2::Value2), h(Enum2::Value2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value2), h(Enum2::Value3));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value2), h(Enum2::Value4));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value3), h(Enum2::Value1));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value3), h(Enum2::Value2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Enum2::Value3), h(Enum2::Value3));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value3), h(Enum2::Value4));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value4), h(Enum2::Value1));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value4), h(Enum2::Value2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(h(Enum2::Value4), h(Enum2::Value3));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(h(Enum2::Value4), h(Enum2::Value4));
	}
}

struct S{};

GTEST_TEST(FunctionalTest, HashTest)
{
	bool_test();

	integral_test<signed char>();
	integral_test<signed short>();
	integral_test<signed int>();
	integral_test<signed long>();
	integral_test<signed long long>();
	integral_test<unsigned char>();
	integral_test<unsigned short>();
	integral_test<unsigned int>();
	integral_test<unsigned long>();
	integral_test<unsigned long long>();

	integral_test<char>();
	integral_test<wchar_t>();
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	integral_test<char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	integral_test<char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	integral_test<char32_t>();
#endif

	float_test<float>();
	float_test<double>();
	float_test<long double>();

	pointer_test<int>();
	pointer_test<char>();
	pointer_test<float>();

	enum_test();

	disabled_hash_test<const int>();
	disabled_hash_test<const float>();
	disabled_hash_test<int&>();
	disabled_hash_test<int&&>();
	disabled_hash_test<void>();
	disabled_hash_test<S>();
}

}	// namespace hash_test

}	// namespace hamon_functional_test

#undef HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ
#undef HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE
