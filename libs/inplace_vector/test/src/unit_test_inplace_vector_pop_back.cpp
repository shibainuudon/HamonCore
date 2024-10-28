/**
 *	@file	unit_test_inplace_vector_pop_back.cpp
 *
 *	@brief	pop_back のテスト
 *
 *	constexpr void pop_back();
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace pop_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
		static_assert(hamon::is_same<decltype(v.pop_back()), void>::value, "");
#if !defined(HAMON_USE_STD_INPLACE_VECTOR)
		static_assert( noexcept(v.pop_back()), "");
#endif
	}
	{
		InplaceVector v{1,2,3};
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		v.pop_back();
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);

		v.pop_back();
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 1);

		v.pop_back();
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
//	VERIFY((test_impl_3<T, 1>()));
//	VERIFY((test_impl_3<T, 2>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 5>()));
	VERIFY((test_impl_3<T, 6>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}


#undef VERIFY

GTEST_TEST(InplaceVectorTest, PopBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/pop_back
	{
		auto print = [](hamon::inplace_vector<int, 4> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<int, 4> numbers {1, 2, 3};
		EXPECT_TRUE(!numbers.empty());
		EXPECT_EQ("1, 2, 3, ", print(numbers));
		numbers.pop_back();
		EXPECT_TRUE(!numbers.empty());
		EXPECT_EQ("1, 2, ", print(numbers));
		numbers.pop_back();
		EXPECT_TRUE(!numbers.empty());
		EXPECT_EQ("1, ", print(numbers));
		numbers.pop_back();
		EXPECT_TRUE(numbers.empty());
		EXPECT_EQ("", print(numbers));
	}
}

}	// namespace pop_back_test

}	// namespace hamon_inplace_vector_test
