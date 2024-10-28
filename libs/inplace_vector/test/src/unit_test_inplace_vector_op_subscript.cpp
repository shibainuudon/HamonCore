/**
 *	@file	unit_test_inplace_vector_op_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr reference       operator[](size_type n);
 *	constexpr const_reference operator[](size_type n) const;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace op_subscript_test
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
		static_assert(hamon::is_same<decltype( v[n]), Reference>::value, "");
		static_assert(hamon::is_same<decltype(cv[n]), ConstReference>::value, "");
#if !defined(HAMON_USE_STD_INPLACE_VECTOR)
		static_assert( noexcept( v[n]), "");
		static_assert( noexcept(cv[n]), "");
#endif
	}
	{
		InplaceVector v{10,20,30};
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);

		v[0] = 11;
		v[2] = 12;

		VERIFY(v[0] == 11);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 12);
	}
	{
		InplaceVector const v{10,20,30};
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
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

GTEST_TEST(InplaceVectorTest, OpSubscriptTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/operator_at
	{
		hamon::inplace_vector<int, 4> numbers{2, 4, 6, 8};

		// Second element
		EXPECT_EQ(4, numbers[1]);

		numbers[0] = 5;

		// All numbers
		EXPECT_EQ(5, numbers[0]);
		EXPECT_EQ(4, numbers[1]);
		EXPECT_EQ(6, numbers[2]);
		EXPECT_EQ(8, numbers[3]);
	}
}

}	// namespace op_subscript_test

}	// namespace hamon_inplace_vector_test
