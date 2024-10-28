/**
 *	@file	unit_test_inplace_vector_reserve.cpp
 *
 *	@brief	reserve のテスト
 *
 *	static constexpr void reserve(size_type n);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace reserve_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using SizeType = typename InplaceVector::size_type;

	{
		InplaceVector const v;
		SizeType const n{};
		static_assert(hamon::is_same<decltype(v.reserve(n)), void>::value, "");
		static_assert(!noexcept(v.reserve(n)), "");
	}
	{
		InplaceVector v;
		v.reserve(0);
		VERIFY(v.size() == 0);
	}
	{
		InplaceVector const v;
		v.reserve(0);
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
		InplaceVector v{1,2};
		VERIFY(v.size() == 2);
		VERIFY(v.max_size() == N);
		v.reserve(0);
		VERIFY(v.size() == 2);
		VERIFY(v.max_size() == N);
		v.reserve(3);
		VERIFY(v.size() == 2);
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

GTEST_TEST(InplaceVectorTest, ReserveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::inplace_vector<int, 0> v;
		EXPECT_NO_THROW(v.reserve(0));
		EXPECT_THROW(v.reserve(1), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<int, 3> v;
		EXPECT_NO_THROW(v.reserve(1));
		EXPECT_NO_THROW(v.reserve(2));
		EXPECT_NO_THROW(v.reserve(3));
		EXPECT_THROW(v.reserve(4), hamon::bad_alloc);
		EXPECT_THROW(v.reserve(5), hamon::bad_alloc);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/reserve
	{
		hamon::inplace_vector<int, 4> v {1, 2, 3};
		EXPECT_TRUE(v.capacity() == 4 && v.size() == 3);

		v.reserve(2); // does nothing
		EXPECT_TRUE(v.capacity() == 4 && v.size() == 3);

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(v.reserve(13), hamon::bad_alloc); // throws, because requested capacity > N; v is left unchanged
		EXPECT_TRUE(v.capacity() == 4 && v.size() == 3);
#endif
	}
}

}	// namespace reserve_test

}	// namespace hamon_inplace_vector_test
