﻿/**
 *	@file	unit_test_inplace_vector_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	constexpr inplace_vector(const inplace_vector&);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace ctor_copy_test
{

struct S1
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S1(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S1()                     = default;
	HAMON_CXX20_CONSTEXPR S1(S1 const&)            = default;
	HAMON_CXX20_CONSTEXPR S1(S1&&)                 = default;
	HAMON_CXX20_CONSTEXPR S1& operator=(S1 const&) = default;
	HAMON_CXX20_CONSTEXPR S1& operator=(S1&&)      = default;
	HAMON_CXX20_CONSTEXPR ~S1()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S1 const& y) const { return m_value == y.m_value; }
};
static_assert( hamon::is_trivially_copy_constructible<S1>::value, "");

struct S2
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S2(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S2()                     = default;
	HAMON_CXX20_CONSTEXPR S2(S2 const& x) : m_value(x.m_value) {}
	HAMON_CXX20_CONSTEXPR S2(S2&&)                 = default;
	HAMON_CXX20_CONSTEXPR S2& operator=(S2 const&) = default;
	HAMON_CXX20_CONSTEXPR S2& operator=(S2&&)      = default;
	HAMON_CXX20_CONSTEXPR ~S2()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S2 const& y) const { return m_value == y.m_value; }
};
static_assert(!hamon::is_trivially_copy_constructible<S2>::value, "");

struct S3
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S3(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S3()                     = default;
	HAMON_CXX20_CONSTEXPR S3(S3 const&)            = default;
	HAMON_CXX20_CONSTEXPR S3(S3&&)                 = default;
	HAMON_CXX20_CONSTEXPR S3& operator=(S3 const&) = default;
	HAMON_CXX20_CONSTEXPR S3& operator=(S3&&)      = default;
	HAMON_CXX20_CONSTEXPR ~S3() {}
	HAMON_CXX20_CONSTEXPR bool operator==(S3 const& y) const { return m_value == y.m_value; }
};
static_assert(!hamon::is_trivially_copy_constructible<S3>::value, "");

struct S4
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S4(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S4() : m_value() {}
	HAMON_CXX20_CONSTEXPR S4(S4 const&) = default;
	HAMON_CXX20_CONSTEXPR S4(S4&& x) : m_value(x.m_value) {}
	HAMON_CXX20_CONSTEXPR S4& operator=(S4 const&) { return *this; }
	HAMON_CXX20_CONSTEXPR S4& operator=(S4&&) { return *this; }
	HAMON_CXX20_CONSTEXPR ~S4() = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S4 const& y) const { return m_value == y.m_value; }
};
static_assert( hamon::is_trivially_copy_constructible<S4>::value, "");

static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<int, 0>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<int, 1>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<float, 0>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<float, 1>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<S1, 0>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<S1, 1>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<S2, 0>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::inplace_vector<S2, 1>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<S3, 0>>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<hamon::inplace_vector<S3, 1>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<S4, 0>>::value, "");
static_assert( hamon::is_trivially_copy_constructible<hamon::inplace_vector<S4, 1>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector const v1;
		InplaceVector v2(v1);
		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector const v1{T{1}, T{2}, T{3}};
		InplaceVector v2(v1);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == T{1});
		VERIFY(v2[1] == T{2});
		VERIFY(v2[2] == T{3});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 2>()));
	VERIFY((test_impl_0<T, 3>()));
	VERIFY((test_impl_0<T, 9>()));

//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
//	VERIFY((test_impl_3<T, 2>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, CtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());
	EXPECT_TRUE(test<S4>());
}

}	// namespace ctor_copy_test

}	// namespace hamon_inplace_vector_test