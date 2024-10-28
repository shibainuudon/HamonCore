/**
 *	@file	unit_test_inplace_vector_capacity.cpp
 *
 *	@brief	capacity のテスト
 *
 *	static constexpr size_type capacity() noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace capacity_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	{
		InplaceVector const v;
		static_assert(hamon::is_same<decltype(v.capacity()), SizeType>::value, "");
		static_assert( noexcept(v.capacity()), "");
	}
	{
		InplaceVector v;
		VERIFY(v.capacity() == N);
	}
	{
		InplaceVector const v;
		VERIFY(v.capacity() == N);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v{1};
		VERIFY(v.capacity() == N);
	}
	{
		InplaceVector v{1,2};
		VERIFY(v.capacity() == N);
	}
	{
		InplaceVector v{1,2,3};
		VERIFY(v.capacity() == N);
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

GTEST_TEST(InplaceVectorTest, CapacityTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/capacity
	{
		constexpr hamon::inplace_vector<int, 4> v1;
		static_assert(v1.capacity() == 4 && v1.max_size() == 4, "");

		constexpr hamon::inplace_vector<int, 0> v2;
		static_assert(v2.capacity() == 0 && v2.max_size() == 0, "");
	}
}

}	// namespace capacity_test

}	// namespace hamon_inplace_vector_test
