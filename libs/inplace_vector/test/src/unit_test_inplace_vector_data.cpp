/**
 *	@file	unit_test_inplace_vector_data.cpp
 *
 *	@brief	data のテスト
 *
 *	constexpr       T* data()       noexcept;
 *	constexpr const T* data() const noexcept;
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/memory.hpp>
#include <hamon/span.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace data_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		InplaceVector const cv;
		static_assert(hamon::is_same<decltype( v.data()), T*>::value, "");
		static_assert(hamon::is_same<decltype(cv.data()), const T*>::value, "");
		static_assert( noexcept( v.data()), "");
		static_assert( noexcept(cv.data()), "");
	}
	{
		InplaceVector v{10,20,30};
		VERIFY(v.data() != nullptr);
		VERIFY(v.data() == hamon::addressof(v.front()));
		VERIFY(*v.data() == 10);

		*v.data() = 42;

		VERIFY(*v.data() == 42);
		VERIFY(v[0] == 42);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
	}
	{
		InplaceVector const v{10,20,30};
		VERIFY(v.data() != nullptr);
		VERIFY(v.data() == hamon::addressof(v.front()));
		VERIFY(*v.data() == 10);
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

GTEST_TEST(InplaceVectorTest, DataTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/data
	{
		auto pointer_func = [](const int* p, hamon::size_t size)
		{
			std::stringstream ss;
			for (hamon::size_t i = 0; i < size; ++i)
			{
				ss << p[i] << ' ';
			}
			EXPECT_EQ("1 2 3 4 ", ss.str());
		};

		auto span_func = [](hamon::span<const int> data) // since C++20
		{
			std::stringstream ss;
			for (const int e : data)
			{
				ss << e << ' ';
			}
			EXPECT_EQ("1 2 3 4 ", ss.str());
		};

		hamon::inplace_vector<int, 4> container {1, 2, 3, 4};

		// Prefer container.data() over &container[0]
		pointer_func(container.data(), container.size());

		// std::span is a safer alternative to separated pointer/size.
		span_func({container.data(), container.size()});
	}
}

}	// namespace data_test

}	// namespace hamon_inplace_vector_test
