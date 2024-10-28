/**
 *	@file	unit_test_inplace_vector_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	static constexpr size_type max_size() noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace max_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	{
		InplaceVector const v;
		static_assert(hamon::is_same<decltype(v.max_size()), SizeType>::value, "");
		static_assert( noexcept(v.max_size()), "");
	}
	{
		InplaceVector v;
		VERIFY(v.max_size() == N);
	}
	{
		InplaceVector const v;
		VERIFY(v.max_size() == N);
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v{1};
		VERIFY(v.max_size() == N);
	}
	{
		InplaceVector v{1,2};
		VERIFY(v.max_size() == N);
	}
	{
		InplaceVector v{1,2,3};
		VERIFY(v.max_size() == N);
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

GTEST_TEST(InplaceVectorTest, MaxSizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace max_size_test

}	// namespace hamon_inplace_vector_test
