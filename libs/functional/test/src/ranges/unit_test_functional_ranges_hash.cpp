/**
 *	@file	unit_test_functional_ranges_hash.cpp
 *
 *	@brief	ranges::hash のテスト
 */

#include <hamon/functional/ranges/hash.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/cstdint/int64_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/array.hpp>
#include <hamon/limits.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <bitset>
#include <memory>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ HAMON_CXX11_CONSTEXPR_EXPECT_EQ
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE HAMON_CXX11_CONSTEXPR_EXPECT_NE
#  define HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ HAMON_CXX14_CONSTEXPR_EXPECT_EQ
#  define HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_NE HAMON_CXX14_CONSTEXPR_EXPECT_NE
#else
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ EXPECT_EQ
#  define HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE EXPECT_NE
#  define HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ EXPECT_EQ
#  define HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_NE EXPECT_NE
#endif

namespace hamon_functional_test
{

namespace ranges_hash_test
{

struct S1
{
private:
	int value;

public:
	HAMON_CXX11_CONSTEXPR S1(int v) : value(v) {}

	HAMON_CXX14_CONSTEXPR hamon::size_t hash() & HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(value * 1);
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t hash() const&
	{
		return static_cast<hamon::size_t>(value * 2);
	}

	HAMON_CXX14_CONSTEXPR hamon::size_t hash() &&
	{
		return static_cast<hamon::size_t>(value * 3);
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t hash() const&& HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(value * 4);
	}
};

GTEST_TEST(FunctionalTest, RangesHashMemberTest)
{
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S1&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S1 const&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S1&&>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S1 const&&>::value, "");

	HAMON_CXX11_CONSTEXPR S1 const s1_1{1};
	HAMON_CXX11_CONSTEXPR S1 const s1_2{2};
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::ranges::hash(s1_1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::ranges::hash(s1_2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::ranges::hash(hamon::move(s1_1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, hamon::ranges::hash(hamon::move(s1_2)));

	S1 s1_3{1};
	S1 s1_4{2};
	EXPECT_EQ(1u, hamon::ranges::hash(s1_3));
	EXPECT_EQ(2u, hamon::ranges::hash(s1_4));
	EXPECT_EQ(3u, hamon::ranges::hash(hamon::move(s1_3)));
	EXPECT_EQ(6u, hamon::ranges::hash(hamon::move(s1_4)));
}

struct S2
{
private:
	int value;

public:
	HAMON_CXX11_CONSTEXPR S2(int v) : value(v) {}

	friend constexpr hamon::size_t hash(S2 & s) HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(s.value * 1);
	}

	friend constexpr hamon::size_t hash(S2 const& s) HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(s.value * 2);
	}
	
	friend constexpr hamon::size_t hash(S2 && s)
	{
		return static_cast<hamon::size_t>(s.value * 3);
	}
	
	friend constexpr hamon::size_t hash(S2 const&& s)
	{
		return static_cast<hamon::size_t>(s.value * 4);
	}
};

GTEST_TEST(FunctionalTest, RangesHashAdlTest)
{
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S2&>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S2 const&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S2&&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), S2 const&&>::value, "");

	HAMON_CXX11_CONSTEXPR S2 const s4_1{3};
	HAMON_CXX11_CONSTEXPR S2 const s4_2{4};
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6u, hamon::ranges::hash(s4_1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8u, hamon::ranges::hash(s4_2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, hamon::ranges::hash(hamon::move(s4_1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, hamon::ranges::hash(hamon::move(s4_2)));

	S2 s4_3{3};
	S2 s4_4{4};
	EXPECT_EQ( 3u, hamon::ranges::hash(s4_3));
	EXPECT_EQ( 4u, hamon::ranges::hash(s4_4));
	EXPECT_EQ( 9u, hamon::ranges::hash(hamon::move(s4_3)));
	EXPECT_EQ(12u, hamon::ranges::hash(hamon::move(s4_4)));
}

template <typename T>
void HashIntegralTest()
{
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), T>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(T(0)), hamon::ranges::hash(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(T( 1)));

	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>(T(0), T(10));
		auto const b = get_random_value<T>(T(0), T(10));
		if (a == b)
		{
			EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		}
		else
		{
			EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(b));
		}
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_EQ(hamon::ranges::hash(b), hamon::ranges::hash(b));
	}
	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>();
		auto const b = get_random_value<T>();
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(a + T(1)));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(a - T(1)));
		EXPECT_EQ(hamon::ranges::hash(b), hamon::ranges::hash(b));
		EXPECT_NE(hamon::ranges::hash(b), hamon::ranges::hash(b + T(1)));
		EXPECT_NE(hamon::ranges::hash(b), hamon::ranges::hash(b - T(1)));
	}
}

GTEST_TEST(FunctionalTest, RangesHashIntegralTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::ranges::hash(false));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::ranges::hash((char)1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::ranges::hash((signed char)2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, hamon::ranges::hash((unsigned char)3));
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::ranges::hash((char8_t)4));
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, hamon::ranges::hash((char16_t)5));
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6u, hamon::ranges::hash((char32_t)6));
#endif
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, hamon::ranges::hash((wchar_t)7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, hamon::ranges::hash((short)8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, hamon::ranges::hash((unsigned short)9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, hamon::ranges::hash((int)10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::ranges::hash((unsigned int)11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, hamon::ranges::hash((long)12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13u, hamon::ranges::hash((unsigned long)13));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(hamon::int64_t( 0)), hamon::ranges::hash(hamon::int64_t( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(hamon::int64_t( 1)), hamon::ranges::hash(hamon::int64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(hamon::int64_t(-1)), hamon::ranges::hash(hamon::int64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(hamon::int64_t( 0)), hamon::ranges::hash(hamon::int64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(hamon::int64_t( 0)), hamon::ranges::hash(hamon::int64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(hamon::int64_t( 1)), hamon::ranges::hash(hamon::int64_t(-1)));

	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t a = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR hamon::int64_t b = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t a = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR hamon::int64_t b = INT64_C(0x7FFFFFFFFFFFFFFE);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::int64_t a = INT64_C(0x3FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR hamon::int64_t b = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(b));
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(hamon::uint64_t( 0)), hamon::ranges::hash(hamon::uint64_t( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(hamon::uint64_t( 1)), hamon::ranges::hash(hamon::uint64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(hamon::uint64_t(-1)), hamon::ranges::hash(hamon::uint64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(hamon::uint64_t( 0)), hamon::ranges::hash(hamon::uint64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(hamon::uint64_t( 0)), hamon::ranges::hash(hamon::uint64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(hamon::uint64_t( 1)), hamon::ranges::hash(hamon::uint64_t(-1)));
	{
		HAMON_CXX11_CONSTEXPR hamon::uint64_t a = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR hamon::uint64_t b = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint64_t a = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR hamon::uint64_t b = UINT64_C(0xFFFFFFFFFFFFFFFE);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::uint64_t a = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR hamon::uint64_t b = UINT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(b));
	}

	HashIntegralTest<signed char>();
	HashIntegralTest<signed short>();
	HashIntegralTest<signed int>();
	HashIntegralTest<signed long>();
	HashIntegralTest<signed long long>();
	HashIntegralTest<unsigned char>();
	HashIntegralTest<unsigned short>();
	HashIntegralTest<unsigned int>();
	HashIntegralTest<unsigned long>();
	HashIntegralTest<unsigned long long>();
}

template <typename T>
void HashFloatTest()
{
//	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), T>::value, "");

	HAMON_CXX11_CONSTEXPR T const eps = hamon::numeric_limits<T>::epsilon();
	HAMON_CXX11_CONSTEXPR T const max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR T const min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR T const low = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR T const inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR T const nan = hamon::numeric_limits<T>::quiet_NaN();

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(T(0)), hamon::ranges::hash(T(0)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(T(1)), hamon::ranges::hash(T(1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(T(-1)), hamon::ranges::hash(T(-1)));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(T(0) + eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(T(0) - eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(1)), hamon::ranges::hash(T(1) + eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(1)), hamon::ranges::hash(T(1) - eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(1)), hamon::ranges::hash(T(-1)));

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(eps), hamon::ranges::hash(eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(max), hamon::ranges::hash(max));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(min), hamon::ranges::hash(min));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(low), hamon::ranges::hash(low));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(inf), hamon::ranges::hash(inf));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(nan), hamon::ranges::hash(nan));

	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(eps));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(max));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(min));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(low));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(inf));
	HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(T(0)), hamon::ranges::hash(nan));

	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>(T(-1), T(1));
		auto const b = get_random_value<T>(T(-1), T(1));
		if (a == b)
		{
			EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		}
		else
		{
			EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(b));
		}
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_EQ(hamon::ranges::hash(b), hamon::ranges::hash(b));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(-a));
		EXPECT_NE(hamon::ranges::hash(b), hamon::ranges::hash(-b));
	}
}

GTEST_TEST(FunctionalTest, RangesHashFloatTest)
{
	HashFloatTest<float>();
	HashFloatTest<double>();
	HashFloatTest<long double>();
}

GTEST_TEST(FunctionalTest, RangesHashPointerTest)
{
//	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), int*>::value, "");
//	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), void*>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), hamon::nullptr_t>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::ranges::hash(nullptr));

	int i = 0;
	int j = 0;
	int* p1 = &i;
	int* p2 = &j;
	int const* cp1 = &i;
	int const* cp2 = &j;

	EXPECT_EQ(hamon::ranges::hash(p1), hamon::ranges::hash(cp1));
	EXPECT_EQ(hamon::ranges::hash(p2), hamon::ranges::hash(cp2));

	EXPECT_NE(hamon::ranges::hash(p1), hamon::ranges::hash(p2));
}

GTEST_TEST(FunctionalTest, RangesHashEnumTest)
{
	enum Enum1
	{
		Value1_1, Value1_2, Value1_3
	};
	enum class Enum2
	{
		Value1, Value2, Value3
	};

	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), Enum1>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::ranges::hash), Enum2>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::ranges::hash(Value1_1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::ranges::hash(Value1_2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::ranges::hash(Value1_3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::ranges::hash(Enum2::Value1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::ranges::hash(Enum2::Value2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::ranges::hash(Enum2::Value3));
}

GTEST_TEST(FunctionalTest, RangesHashArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR const char a[] = "abcde";
		HAMON_CXX11_CONSTEXPR const char b[] = "abcde";
		HAMON_CXX11_CONSTEXPR const char c[] = "abcda";
		HAMON_CXX11_CONSTEXPR const char d[] = "abcd";

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(d));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR int b[] = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR int c[] = {3, 2, 1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
	}
	{
		HAMON_CXX11_CONSTEXPR float a[] = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR float b[] = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR float c[] = {0.0f, 0.5f, -1.5f};
		HAMON_CXX11_CONSTEXPR float d[] = {0.0f, 0.5f, -1.5f, 2.0f, 0.0f};
		HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
		HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(d));
	}
}

GTEST_TEST(FunctionalTest, RangesHashStdArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> a = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> b = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> c = {2, 3, 1};

		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<float, 4> a = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR hamon::array<float, 4> b = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR hamon::array<float, 3> c = {0.0f, 0.5f, -1.5f};
		HAMON_CXX11_CONSTEXPR hamon::array<float, 5> d = {0.0f, 0.5f, -1.5f, 2.0f, 0.0f};
		HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
		HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(d));
	}
}

GTEST_TEST(FunctionalTest, RangesHashVectorTest)
{
	{
		const hamon::vector<int> a;
		EXPECT_EQ(0u, hamon::ranges::hash(a));
	}
	{
		const hamon::vector<int> a = {1, 2, 3};
		const hamon::vector<int> b = {1, 2, 3};
		const hamon::vector<int> c = {1,-2, 3};

		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
	}
	{
		const hamon::vector<float> a = {0.0f, 0.5f, -1.5f, 2.0f};
		const hamon::vector<float> b = {0.0f, 0.5f, -1.5f, 2.0f};
		const hamon::vector<float> c = {0.0f, 0.5f, -1.5f};
		const hamon::vector<float> d = {0.0f, 0.5f, -1.5f, 2.0f, 0.0f};
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(d));
	}
}

GTEST_TEST(FunctionalTest, RangesHashListTest)
{
	{
		const hamon::list<int> a;
		EXPECT_EQ(0u, hamon::ranges::hash(a));
	}
	{
		const hamon::list<int> a = {1, 2, 3};
		const hamon::list<int> b = {1, 2, 3};
		const hamon::list<int> c = {1,-2, 3};

		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
	}
	{
		const hamon::list<float> a = {0.0f, 0.5f, -1.5f, 2.0f};
		const hamon::list<float> b = {0.0f, 0.5f, -1.5f, 2.0f};
		const hamon::list<float> c = {0.0f, 0.5f, -1.5f, 2.1f};
		const hamon::list<float> d = {0.1f, 0.5f, -1.5f, 2.0f};
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(a));
		EXPECT_EQ(hamon::ranges::hash(a), hamon::ranges::hash(b));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(c));
		EXPECT_NE(hamon::ranges::hash(a), hamon::ranges::hash(d));
	}
}

GTEST_TEST(FunctionalTest, RangesHashStringTest)
{
	{
		const hamon::string s;
		EXPECT_EQ(0u, hamon::ranges::hash(s));
	}
	{
		const hamon::string s = "Hello World";
		const hamon::size_t expect =
			sizeof(hamon::size_t) == 4 ?
			0x30E5A5D0u :
			0xC157F621C07CE515;
		EXPECT_EQ(expect, hamon::ranges::hash(s));
	}
}

GTEST_TEST(FunctionalTest, RangesHashPairTest)
{
	{
		HAMON_CXX14_CONSTEXPR std::pair<int, float> p {1, 2.5f};
		HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash_combine(0, 1, 2.5f), hamon::ranges::hash(p));
	}
	{
		HAMON_CXX14_CONSTEXPR std::pair<S1, S2> p{S1{3}, S2{4}};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash_combine(0, 3*2, 4*2), hamon::ranges::hash(p));
	}
}

GTEST_TEST(FunctionalTest, RangesHashTupleTest)
{
	{
		HAMON_CXX14_CONSTEXPR std::tuple<> t;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash_combine(0), hamon::ranges::hash(t));
	}
	{
		HAMON_CXX14_CONSTEXPR std::tuple<int> t{2};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash_combine(0, 2), hamon::ranges::hash(t));
	}
	{
		HAMON_CXX14_CONSTEXPR std::tuple<int, int> t{3, 4};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash_combine(0, 3, 4), hamon::ranges::hash(t));
	}
	{
		HAMON_CXX14_CONSTEXPR std::tuple<S1, float, S2, int> t{S1{4}, 5.5f, S2{6}, 7};
		HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::ranges::hash_combine(0, 4*2, 5.5f, 6*2, 7), hamon::ranges::hash(t));
	}
}

GTEST_TEST(FunctionalTest, RangesHashBitsetTest)
{
	{
		HAMON_CXX11_CONSTEXPR std::bitset<4> b;
		EXPECT_EQ(std::hash<std::bitset<4>>{}(b), hamon::ranges::hash(b));
	}
}

GTEST_TEST(FunctionalTest, RangesHashUniquePtrTest)
{
	{
		std::unique_ptr<S1> p;
		EXPECT_EQ(std::hash<std::unique_ptr<S1>>{}(p), hamon::ranges::hash(p));
	}
	{
		std::unique_ptr<S1> p(new S1(42));
		EXPECT_EQ(std::hash<std::unique_ptr<S1>>{}(p), hamon::ranges::hash(p));
	}
}

}	// namespace ranges_hash_test

}	// namespace hamon_functional_test

#undef HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_EQ
#undef HAMON_CXX11_BIT_CAST_CONSTEXPR_EXPECT_NE
#undef HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_EQ
#undef HAMON_CXX14_BIT_CAST_CONSTEXPR_EXPECT_NE
