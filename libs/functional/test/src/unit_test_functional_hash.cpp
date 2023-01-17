/**
 *	@file	unit_test_functional_hash.cpp
 *
 *	@brief	hash のテスト
 */

#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <bitset>
#include <memory>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ HAMON_CXX20_CONSTEXPR_EXPECT_EQ
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE HAMON_CXX20_CONSTEXPR_EXPECT_NE
#else
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ EXPECT_EQ
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE EXPECT_NE
#endif

namespace hamon_functional_test
{

namespace hash_test
{

struct S1
{
private:
	int value;

public:
	HAMON_CXX11_CONSTEXPR S1(int v) : value(v) {}

	HAMON_CXX14_CONSTEXPR std::size_t hash() & HAMON_NOEXCEPT
	{
		return static_cast<std::size_t>(value * 1);
	}

	HAMON_CXX11_CONSTEXPR std::size_t hash() const&
	{
		return static_cast<std::size_t>(value * 2);
	}

	HAMON_CXX14_CONSTEXPR std::size_t hash() &&
	{
		return static_cast<std::size_t>(value * 3);
	}

	HAMON_CXX11_CONSTEXPR std::size_t hash() const&& HAMON_NOEXCEPT
	{
		return static_cast<std::size_t>(value * 4);
	}
};

GTEST_TEST(FunctionalTest, HashMemberTest)
{
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), S1&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::hash), S1 const&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::hash), S1&&>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), S1 const&&>::value, "");

	HAMON_CXX11_CONSTEXPR S1 const s1_1{1};
	HAMON_CXX11_CONSTEXPR S1 const s1_2{2};
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::hash(s1_1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::hash(s1_2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::hash(std::move(s1_1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, hamon::hash(std::move(s1_2)));

	S1 s1_3{1};
	S1 s1_4{2};
	EXPECT_EQ(1u, hamon::hash(s1_3));
	EXPECT_EQ(2u, hamon::hash(s1_4));
	EXPECT_EQ(3u, hamon::hash(std::move(s1_3)));
	EXPECT_EQ(6u, hamon::hash(std::move(s1_4)));
}

struct S2
{
private:
	int value;

public:
	HAMON_CXX11_CONSTEXPR S2(int v) : value(v) {}

	friend constexpr std::size_t hash(S2 & s) HAMON_NOEXCEPT
	{
		return static_cast<std::size_t>(s.value * 1);
	}

	friend constexpr std::size_t hash(S2 const& s) HAMON_NOEXCEPT
	{
		return static_cast<std::size_t>(s.value * 2);
	}
	
	friend constexpr std::size_t hash(S2 && s)
	{
		return static_cast<std::size_t>(s.value * 3);
	}
	
	friend constexpr std::size_t hash(S2 const&& s)
	{
		return static_cast<std::size_t>(s.value * 4);
	}
};

GTEST_TEST(FunctionalTest, HashAdlTest)
{
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), S2&>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), S2 const&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::hash), S2&&>::value, "");
	static_assert(!hamon::is_nothrow_invocable<decltype(hamon::hash), S2 const&&>::value, "");

	HAMON_CXX11_CONSTEXPR S2 const s4_1{3};
	HAMON_CXX11_CONSTEXPR S2 const s4_2{4};
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6u, hamon::hash(s4_1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8u, hamon::hash(s4_2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, hamon::hash(std::move(s4_1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, hamon::hash(std::move(s4_2)));

	S2 s4_3{3};
	S2 s4_4{4};
	EXPECT_EQ( 3u, hamon::hash(s4_3));
	EXPECT_EQ( 4u, hamon::hash(s4_4));
	EXPECT_EQ( 9u, hamon::hash(std::move(s4_3)));
	EXPECT_EQ(12u, hamon::hash(std::move(s4_4)));
}

template <typename T>
void HashIntegralTest()
{
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), T>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(T(0)), hamon::hash(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(T( 1)));

	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>(T(0), T(10));
		auto const b = get_random_value<T>(T(0), T(10));
		if (a == b)
		{
			EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		}
		else
		{
			EXPECT_NE(hamon::hash(a), hamon::hash(b));
		}
		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_EQ(hamon::hash(b), hamon::hash(b));
	}
	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>();
		auto const b = get_random_value<T>();
		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_NE(hamon::hash(a), hamon::hash(a + T(1)));
		EXPECT_NE(hamon::hash(a), hamon::hash(a - T(1)));
		EXPECT_EQ(hamon::hash(b), hamon::hash(b));
		EXPECT_NE(hamon::hash(b), hamon::hash(b + T(1)));
		EXPECT_NE(hamon::hash(b), hamon::hash(b - T(1)));
	}
}

GTEST_TEST(FunctionalTest, HashIntegralTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(false));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::hash((char)1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::hash((signed char)2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, hamon::hash((unsigned char)3));
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::hash((char8_t)4));
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, hamon::hash((char16_t)5));
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6u, hamon::hash((char32_t)6));
#endif
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, hamon::hash((wchar_t)7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, hamon::hash((short)8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, hamon::hash((unsigned short)9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, hamon::hash((int)10));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::hash((unsigned int)11));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, hamon::hash((long)12));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13u, hamon::hash((unsigned long)13));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(std::int64_t( 0)), hamon::hash(std::int64_t( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(std::int64_t( 1)), hamon::hash(std::int64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(std::int64_t(-1)), hamon::hash(std::int64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(std::int64_t( 0)), hamon::hash(std::int64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(std::int64_t( 0)), hamon::hash(std::int64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(std::int64_t( 1)), hamon::hash(std::int64_t(-1)));

	{
		HAMON_CXX11_CONSTEXPR std::int64_t a = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR std::int64_t b = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t a = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR std::int64_t b = INT64_C(0x7FFFFFFFFFFFFFFE);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t a = INT64_C(0x3FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR std::int64_t b = INT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(b));
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(std::uint64_t( 0)), hamon::hash(std::uint64_t( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(std::uint64_t( 1)), hamon::hash(std::uint64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(std::uint64_t(-1)), hamon::hash(std::uint64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(std::uint64_t( 0)), hamon::hash(std::uint64_t( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(std::uint64_t( 0)), hamon::hash(std::uint64_t(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(std::uint64_t( 1)), hamon::hash(std::uint64_t(-1)));
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t a = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR std::uint64_t b = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t a = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR std::uint64_t b = UINT64_C(0xFFFFFFFFFFFFFFFE);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(b));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t a = UINT64_C(0xFFFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR std::uint64_t b = UINT64_C(0x7FFFFFFFFFFFFFFF);
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(b));
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
//	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), T>::value, "");

	HAMON_CXX11_CONSTEXPR T const eps = std::numeric_limits<T>::epsilon();
	HAMON_CXX11_CONSTEXPR T const max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR T const min = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR T const low = std::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR T const inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR T const nan = std::numeric_limits<T>::quiet_NaN();

	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(T(0)), hamon::hash(T(0)));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(T(1)), hamon::hash(T(1)));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(T(-1)), hamon::hash(T(-1)));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(T(0) + eps));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(T(0) - eps));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(1)), hamon::hash(T(1) + eps));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(1)), hamon::hash(T(1) - eps));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(1)), hamon::hash(T(-1)));

	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(eps), hamon::hash(eps));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(max), hamon::hash(max));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(min), hamon::hash(min));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(low), hamon::hash(low));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(inf), hamon::hash(inf));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(nan), hamon::hash(nan));

	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(eps));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(max));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(min));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(low));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(inf));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(T(0)), hamon::hash(nan));

	for (int i = 0; i < 100; ++i)
	{
		auto const a = get_random_value<T>(T(-1), T(1));
		auto const b = get_random_value<T>(T(-1), T(1));
		if (a == b)
		{
			EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		}
		else
		{
			EXPECT_NE(hamon::hash(a), hamon::hash(b));
		}
		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_EQ(hamon::hash(b), hamon::hash(b));
		EXPECT_NE(hamon::hash(a), hamon::hash(-a));
		EXPECT_NE(hamon::hash(b), hamon::hash(-b));
	}
}

GTEST_TEST(FunctionalTest, HashFloatTest)
{
	HashFloatTest<float>();
	HashFloatTest<double>();
	HashFloatTest<long double>();
}

GTEST_TEST(FunctionalTest, HashPointerTest)
{
//	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), int*>::value, "");
//	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), void*>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), std::nullptr_t>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(nullptr));

	int i = 0;
	int j = 0;
	int* p1 = &i;
	int* p2 = &j;
	int const* cp1 = &i;
	int const* cp2 = &j;

	EXPECT_EQ(hamon::hash(p1), hamon::hash(cp1));
	EXPECT_EQ(hamon::hash(p2), hamon::hash(cp2));

	EXPECT_NE(hamon::hash(p1), hamon::hash(p2));
}

GTEST_TEST(FunctionalTest, HashEnumTest)
{
	enum Enum1
	{
		Value1_1, Value1_2, Value1_3
	};
	enum class Enum2
	{
		Value1, Value2, Value3
	};

	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), Enum1>::value, "");
	static_assert( hamon::is_nothrow_invocable<decltype(hamon::hash), Enum2>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(Value1_1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::hash(Value1_2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::hash(Value1_3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(Enum2::Value1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, hamon::hash(Enum2::Value2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, hamon::hash(Enum2::Value3));
}

GTEST_TEST(FunctionalTest, HashArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR const char a[] = "abcde";
		HAMON_CXX11_CONSTEXPR const char b[] = "abcde";
		HAMON_CXX11_CONSTEXPR const char c[] = "abcda";
		HAMON_CXX11_CONSTEXPR const char d[] = "abcd";

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(c));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(d));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR int b[] = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR int c[] = {3, 2, 1};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(c));
	}
	{
		HAMON_CXX11_CONSTEXPR float a[] = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR float b[] = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR float c[] = {0.0f, 0.5f, -1.5f};
		HAMON_CXX11_CONSTEXPR float d[] = {0.0f, 0.5f, -1.5f, 2.0f, 0.0f};
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(c));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(d));
	}
}

GTEST_TEST(FunctionalTest, HashStdArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR std::array<int, 3> a = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR std::array<int, 3> b = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR std::array<int, 3> c = {2, 3, 1};

		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(c));
	}
	{
		HAMON_CXX11_CONSTEXPR std::array<float, 4> a = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR std::array<float, 4> b = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR std::array<float, 3> c = {0.0f, 0.5f, -1.5f};
		HAMON_CXX11_CONSTEXPR std::array<float, 5> d = {0.0f, 0.5f, -1.5f, 2.0f, 0.0f};
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(c));
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE(hamon::hash(a), hamon::hash(d));
	}
}

GTEST_TEST(FunctionalTest, HashVectorTest)
{
	{
		const std::vector<int> a;
		EXPECT_EQ(0u, hamon::hash(a));
	}
	{
		const std::vector<int> a = {1, 2, 3};
		const std::vector<int> b = {1, 2, 3};
		const std::vector<int> c = {1,-2, 3};

		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		EXPECT_NE(hamon::hash(a), hamon::hash(c));
	}
	{
		const std::vector<float> a = {0.0f, 0.5f, -1.5f, 2.0f};
		const std::vector<float> b = {0.0f, 0.5f, -1.5f, 2.0f};
		const std::vector<float> c = {0.0f, 0.5f, -1.5f};
		const std::vector<float> d = {0.0f, 0.5f, -1.5f, 2.0f, 0.0f};
		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		EXPECT_NE(hamon::hash(a), hamon::hash(c));
		EXPECT_NE(hamon::hash(a), hamon::hash(d));
	}
}

GTEST_TEST(FunctionalTest, HashListTest)
{
	{
		const std::list<int> a;
		EXPECT_EQ(0u, hamon::hash(a));
	}
	{
		const std::list<int> a = {1, 2, 3};
		const std::list<int> b = {1, 2, 3};
		const std::list<int> c = {1,-2, 3};

		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		EXPECT_NE(hamon::hash(a), hamon::hash(c));
	}
	{
		const std::list<float> a = {0.0f, 0.5f, -1.5f, 2.0f};
		const std::list<float> b = {0.0f, 0.5f, -1.5f, 2.0f};
		const std::list<float> c = {0.0f, 0.5f, -1.5f, 2.1f};
		const std::list<float> d = {0.1f, 0.5f, -1.5f, 2.0f};
		EXPECT_EQ(hamon::hash(a), hamon::hash(a));
		EXPECT_EQ(hamon::hash(a), hamon::hash(b));
		EXPECT_NE(hamon::hash(a), hamon::hash(c));
		EXPECT_NE(hamon::hash(a), hamon::hash(d));
	}
}

GTEST_TEST(FunctionalTest, HashStringTest)
{
	{
		const std::string s;
		EXPECT_EQ(0u, hamon::hash(s));
	}
	{
		const std::string s = "Hello World";
		const std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x30E5A5D0u :
			0xC157F621C07CE515;
		EXPECT_EQ(expect, hamon::hash(s));
	}
}

GTEST_TEST(FunctionalTest, HashPairTest)
{
	{
		HAMON_CXX14_CONSTEXPR std::pair<int, float> p {1, 2.5f};
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash_combine(0, 1, 2.5f), hamon::hash(p));
	}
	{
		HAMON_CXX14_CONSTEXPR std::pair<S1, S2> p{S1{3}, S2{4}};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::hash_combine(0, 3*2, 4*2), hamon::hash(p));
	}
}

GTEST_TEST(FunctionalTest, HashTupleTest)
{
	{
		HAMON_CXX14_CONSTEXPR std::tuple<> t;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::hash_combine(0), hamon::hash(t));
	}
	{
		HAMON_CXX14_CONSTEXPR std::tuple<int> t{2};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::hash_combine(0, 2), hamon::hash(t));
	}
	{
		HAMON_CXX14_CONSTEXPR std::tuple<int, int> t{3, 4};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::hash_combine(0, 3, 4), hamon::hash(t));
	}
	{
		HAMON_CXX14_CONSTEXPR std::tuple<S1, float, S2, int> t{S1{4}, 5.5f, S2{6}, 7};
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(hamon::hash_combine(0, 4*2, 5.5f, 6*2, 7), hamon::hash(t));
	}
}

GTEST_TEST(FunctionalTest, HashBitsetTest)
{
	{
		HAMON_CXX11_CONSTEXPR std::bitset<4> b;
		EXPECT_EQ(std::hash<std::bitset<4>>{}(b), hamon::hash(b));
	}
}

GTEST_TEST(FunctionalTest, HashUniquePtrTest)
{
	{
		std::unique_ptr<S1> p;
		EXPECT_EQ(std::hash<std::unique_ptr<S1>>{}(p), hamon::hash(p));
	}
	{
		std::unique_ptr<S1> p(new S1(42));
		EXPECT_EQ(std::hash<std::unique_ptr<S1>>{}(p), hamon::hash(p));
	}
}

}	// namespace hash_test

}	// namespace hamon_functional_test

#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ
#undef HAMON_BIT_CAST_CONSTEXPR_EXPECT_NE
