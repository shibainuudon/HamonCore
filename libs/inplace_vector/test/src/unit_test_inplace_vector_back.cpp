/**
 *	@file	unit_test_inplace_vector_back.cpp
 *
 *	@brief	back のテスト
 *
 *	constexpr reference       back();
 *	constexpr const_reference back() const;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Reference = typename InplaceVector::reference;
	using ConstReference = typename InplaceVector::const_reference;

	{
		InplaceVector v;
		InplaceVector const cv;
		static_assert(hamon::is_same<decltype( v.back()), Reference>::value, "");
		static_assert(hamon::is_same<decltype(cv.back()), ConstReference>::value, "");
#if !defined(HAMON_USE_STD_INPLACE_VECTOR)
		static_assert( noexcept( v.back()), "");
		static_assert( noexcept(cv.back()), "");
#endif
	}
	{
		InplaceVector v{10,20,30};
		VERIFY(v.back() == 30);

		v.back() = 42;

		VERIFY(v.back() == 42);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 42);
	}
	{
		InplaceVector const v{10,20,30};
		VERIFY(v.back() == 30);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 5>()));
	VERIFY((test_impl_3<T, 6>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, BackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/back
	{
		hamon::inplace_vector<char, 4> letters {'a', 'b', 'c', 'd'};
		EXPECT_TRUE(letters.back() == 'd');
	}
}

}	// namespace back_test

}	// namespace hamon_inplace_vector_test
