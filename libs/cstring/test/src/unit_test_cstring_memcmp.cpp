/**
 *	@file	unit_test_cstring_memcmp.cpp
 *
 *	@brief	memcmpのテスト
 */

#include <hamon/cstring/memcmp.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cstring_test
{
namespace memcmp_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test_int()
{
	const int a1[] = { 0, 1, 2, 3 };
	const int a2[] = { 0, 1, 2, 3 };
	const int a3[] = { 1, 1, 2, 3 };
	const int a4[] = { 0, 1, 2, 0 };
	const int a5[] = { 0, 1, 2, 3, 4 };

	VERIFY(hamon::memcmp(a1, a1, sizeof(a1)) == 0);
	VERIFY(hamon::memcmp(a1, a2, sizeof(a1)) == 0);
	VERIFY(hamon::memcmp(a1, a3, sizeof(a1)) <  0);
	VERIFY(hamon::memcmp(a1, a4, sizeof(a1)) >  0);
	VERIFY(hamon::memcmp(a1, a5, sizeof(a1)) == 0);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test_string()
{
	char a1[] = "abc";
	char a2[] = "abd";

	VERIFY(hamon::memcmp(a1, a1, sizeof(a1)) == 0);
	VERIFY(hamon::memcmp(a1, a2, sizeof(a1)) <  0);
	VERIFY(hamon::memcmp(a2, a1, sizeof(a1)) >  0);
	VERIFY(hamon::memcmp(a2, a2, sizeof(a1)) == 0);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test_float()
{
	{
		float x = 1.0f;
		float y = 1.0f;
		float z = 1.5f;
		VERIFY(hamon::memcmp(&x, &y, sizeof(x)) == 0);
		VERIFY(hamon::memcmp(&x, &z, sizeof(x)) != 0);
	}
	{
		// +0.0 と -0.0
		float x = +0.0f;
		float y = -0.0f;
		VERIFY(x == y);									// 比較演算子では等しい
		VERIFY(hamon::memcmp(&x, &y, sizeof(x)) != 0);	// バイト単位の比較では等しくない
	}
	{
		// nan どうしの比較
		float x = hamon::numeric_limits<float>::quiet_NaN();
		float y = hamon::numeric_limits<float>::quiet_NaN();
		VERIFY(x != y);									// 比較演算子では等しくない
		VERIFY(hamon::memcmp(&x, &y, sizeof(x)) == 0);	// バイト単位の比較では等しい
	}
	return true;
}

struct S
{
	int value;
};

inline HAMON_CXX14_CONSTEXPR bool test_struct()
{
	S s1{10};
	S s2{20};
	S s3{10};
	VERIFY(hamon::memcmp(&s1, &s2, sizeof(S)) != 0);
	VERIFY(hamon::memcmp(&s1, &s3, sizeof(S)) == 0);
	return true;
}

#undef VERIFY

GTEST_TEST(CStringTest, MemCmpTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_int());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_string());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_float());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_struct());
}

}	// namespace memcmp_test
}	// namespace hamon_cstring_test
