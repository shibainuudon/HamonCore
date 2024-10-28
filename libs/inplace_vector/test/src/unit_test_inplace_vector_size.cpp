/**
 *	@file	unit_test_inplace_vector_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	{
		InplaceVector const v;
		static_assert(hamon::is_same<decltype(v.size()), SizeType>::value, "");
		static_assert( noexcept(v.size()), "");
	}
	{
		InplaceVector v;
		VERIFY(v.size() == 0);
	}
	{
		InplaceVector const v;
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		VERIFY(v.size() == 0);
		v.push_back(1);
		VERIFY(v.size() == 1);
		v.clear();
		VERIFY(v.size() == 0);
	}
	{
		InplaceVector v{1,2,3};
		VERIFY(v.size() == 3);
		v.clear();
		VERIFY(v.size() == 0);
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

GTEST_TEST(InplaceVectorTest, SizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/size
	{
		hamon::inplace_vector<int, 4> nums;
		EXPECT_TRUE(nums.size() == 0);
		nums = {1, 2, 3, 4};
		EXPECT_TRUE(nums.size() == 4);
	}
}

}	// namespace size_test

}	// namespace hamon_inplace_vector_test
