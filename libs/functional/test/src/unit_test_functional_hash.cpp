/**
 *	@file	unit_test_functional_hash.cpp
 *
 *	@brief	hash のテスト
 */

#include <hamon/functional/hash.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <bitset>
#include <memory>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ HAMON_CXX20_CONSTEXPR_EXPECT_EQ
#else
#  define HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ EXPECT_EQ
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

	HAMON_CXX14_CONSTEXPR std::size_t hash() &
	{
		return value * 1;
	}

	HAMON_CXX11_CONSTEXPR std::size_t hash() const&
	{
		return value * 2;
	}

	HAMON_CXX14_CONSTEXPR std::size_t hash() &&
	{
		return value * 3;
	}

	HAMON_CXX11_CONSTEXPR std::size_t hash() const&&
	{
		return value * 4;
	}
};

GTEST_TEST(FunctionalTest, HashMemberTest)
{
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

	friend constexpr std::size_t hash(S2 & s)
	{
		return s.value * 1;
	}

	friend constexpr std::size_t hash(S2 const& s)
	{
		return s.value * 2;
	}
	
	friend constexpr std::size_t hash(S2 && s)
	{
		return s.value * 3;
	}
	
	friend constexpr std::size_t hash(S2 const&& s)
	{
		return s.value * 4;
	}
};

GTEST_TEST(FunctionalTest, HashAdlTest)
{
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
	{
		HAMON_CXX11_CONSTEXPR std::int64_t a = 14;
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x9E377D44ULL :
			14;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		HAMON_CXX11_CONSTEXPR std::int64_t a = 0xFFFFFFFFFFFFFFFFULL;
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x21C88688ULL :
			0xFFFFFFFFFFFFFFFFULL;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t a = 15;
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x9E377D84ULL :
			15;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		HAMON_CXX11_CONSTEXPR std::uint64_t a = 0xFFFFFFFFFFFFFFFFULL;
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x21C88688ULL :
			0xFFFFFFFFFFFFFFFFULL;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
}

GTEST_TEST(FunctionalTest, HashFloatTest)
{
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(0.0f));
	HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(0x3f000000u, hamon::hash(0.5f));
//	HAMON_CXX20_CONSTEXPR_EXPECT_EQ(0x4004000000000000u, hamon::hash(2.5));
}

GTEST_TEST(FunctionalTest, HashPointerTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(nullptr));

	int i = 0;
	int* p = &i;
	int const* cp = &i;

	EXPECT_EQ((std::size_t)&i, hamon::hash(p));
	EXPECT_EQ((std::size_t)&i, hamon::hash(cp));
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

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(Value1_1));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1u, hamon::hash(Value1_2));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2u, hamon::hash(Value1_3));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0u, hamon::hash(Enum2::Value1));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1u, hamon::hash(Enum2::Value2));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2u, hamon::hash(Enum2::Value3));
}

GTEST_TEST(FunctionalTest, HashArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0xFB58D153u :
			0x44DF543DFB06F3DAu;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		HAMON_CXX11_CONSTEXPR float a[] = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x3C2D221Au :
			0xD357157CC35DF290u;
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
}

GTEST_TEST(FunctionalTest, HashStdArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR std::array<int, 3> a = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0xFB58D153u :
			0x44DF543DFB06F3DAu;
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		HAMON_CXX11_CONSTEXPR std::array<float, 4> a = {0.0f, 0.5f, -1.5f, 2.0f};
		HAMON_CXX11_CONSTEXPR std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x3C2D221Au :
			0xD357157CC35DF290u;
		HAMON_BIT_CAST_CONSTEXPR_EXPECT_EQ(expect, hamon::hash(a));
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
		const std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0xFB58D153u :
			0x44DF543DFB06F3DAu;
		EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		const std::vector<float> a = {0.0f, 0.5f, -1.5f, 2.0f};
		const std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x3C2D221Au :
			0xD357157CC35DF290u;
		EXPECT_EQ(expect, hamon::hash(a));
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
		const std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0xFB58D153u :
			0x44DF543DFB06F3DAu;
		EXPECT_EQ(expect, hamon::hash(a));
	}
	{
		const std::list<float> a = {0.0f, 0.5f, -1.5f, 2.0f};
		const std::size_t expect =
			sizeof(std::size_t) == 4 ?
			0x3C2D221Au :
			0xD357157CC35DF290u;
		EXPECT_EQ(expect, hamon::hash(a));
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
		std::pair<int, float> p {1, 2.5f};
		EXPECT_EQ(hamon::hash_combine(0, 1, 2.5f), hamon::hash(p));
	}
	{
		std::pair<S1, S2> p{S1{3}, S2{4}};
		EXPECT_EQ(hamon::hash_combine(0, 3*2, 4*2), hamon::hash(p));
	}
}

GTEST_TEST(FunctionalTest, HashTupleTest)
{
	{
		std::tuple<> t;
		EXPECT_EQ(hamon::hash_combine(0), hamon::hash(t));
	}
	{
		std::tuple<int> t{2};
		EXPECT_EQ(hamon::hash_combine(0, 2), hamon::hash(t));
	}
	{
		std::tuple<int, int> t{3, 4};
		EXPECT_EQ(hamon::hash_combine(0, 3, 4), hamon::hash(t));
	}
	{
		std::tuple<S1, float, S2, int> t{S1{4}, 5.5f, S2{6}, 7};
		EXPECT_EQ(hamon::hash_combine(0, 4*2, 5.5f, 6*2, 7), hamon::hash(t));
	}
}

GTEST_TEST(FunctionalTest, HashBitsetTest)
{
	{
		std::bitset<4> b;
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
