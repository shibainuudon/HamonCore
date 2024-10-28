/**
 *	@file	unit_test_inplace_vector_at.cpp
 *
 *	@brief	at のテスト
 *
 *	constexpr reference       at(size_type n);
 *	constexpr const_reference at(size_type n) const;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace at_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;
	using Reference = typename InplaceVector::reference;
	using ConstReference = typename InplaceVector::const_reference;

	{
		InplaceVector v;
		InplaceVector const cv;
		SizeType const n{};
		static_assert(hamon::is_same<decltype( v.at(n)), Reference>::value, "");
		static_assert(hamon::is_same<decltype(cv.at(n)), ConstReference>::value, "");
		static_assert(!noexcept( v.at(n)), "");
		static_assert(!noexcept(cv.at(n)), "");
	}
	{
		InplaceVector v{10,20,30};
		VERIFY(v.at(0) == 10);
		VERIFY(v.at(1) == 20);
		VERIFY(v.at(2) == 30);

		v.at(0) = 11;
		v.at(2) = 12;

		VERIFY(v.at(0) == 11);
		VERIFY(v.at(1) == 20);
		VERIFY(v.at(2) == 12);
	}
	{
		InplaceVector const v{10,20,30};
		VERIFY(v.at(0) == 10);
		VERIFY(v.at(1) == 20);
		VERIFY(v.at(2) == 30);
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

GTEST_TEST(InplaceVectorTest, AtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	{
		hamon::inplace_vector<int, 10> v{1,2,3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}
	{
		hamon::inplace_vector<int, 10> const v{1,2,3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}

	// https://en.cppreference.com/w/cpp/container/inplace_vector/at
	{
		hamon::inplace_vector<int, 6> data {1, 2, 4, 5, 5, 6};

		// Set element 1
		data.at(1) = 88;

		// Read element 2
		EXPECT_EQ(4, data.at(2));

		EXPECT_EQ(6u, data.size());

#if !defined(HAMON_NO_EXCEPTIONS)
		// Try to set an element at random position >= size()
		EXPECT_THROW(data.at(data.size()) = 13, hamon::out_of_range);
#endif

		EXPECT_EQ( 1, data.at(0));
		EXPECT_EQ(88, data.at(1));
		EXPECT_EQ( 4, data.at(2));
		EXPECT_EQ( 5, data.at(3));
		EXPECT_EQ( 5, data.at(4));
		EXPECT_EQ( 6, data.at(5));
	}
}

}	// namespace at_test

}	// namespace hamon_inplace_vector_test
