/**
 *	@file	unit_test_inplace_vector_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector const v;
		static_assert(hamon::is_same<decltype(v.empty()), bool>::value, "");
		static_assert( noexcept(v.empty()), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
	}
	{
		InplaceVector const v;
		VERIFY(v.empty());
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY( v.empty());
		v.push_back(1);
		VERIFY(!v.empty());
		v.clear();
		VERIFY( v.empty());
	}
	{
		InplaceVector v{1,2,3};
		VERIFY(!v.empty());
		v.clear();
		VERIFY( v.empty());
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 3>()));
	VERIFY((test_impl_0<T, 9>()));
	VERIFY((test_impl_0<T, 10>()));

//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 9>()));
	VERIFY((test_impl_3<T, 10>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/empty
	{
		hamon::inplace_vector<char, 8> v;
		EXPECT_TRUE(v.empty());

		v.push_back('_');
		EXPECT_TRUE(not v.empty());
	}
}

}	// namespace empty_test

}	// namespace hamon_inplace_vector_test
