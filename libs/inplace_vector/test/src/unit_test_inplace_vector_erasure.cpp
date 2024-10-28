/**
 *	@file	unit_test_inplace_vector_erasure.cpp
 *
 *	@brief	erase, erase_if のテスト
 *
 *	template<class T, size_t N, class U = T>
 *	constexpr typename inplace_vector<T, N>::size_type
 *	erase(inplace_vector<T, N>& c, const U& value);
 *
 *	template<class T, size_t N, class Predicate>
 *	constexpr typename inplace_vector<T, N>::size_type
 *	erase_if(inplace_vector<T, N>& c, Predicate pred);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/complex.hpp>
#include <hamon/numeric/iota.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace erasure_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	{
		hamon::inplace_vector<int, 10> v = {3,1,4,5,2};
		auto r = hamon::erase(v, 1);
		VERIFY(r == 1);
		const int v2[] = {3,4,5,2};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::inplace_vector<int, 20> v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9};
		auto r = hamon::erase(v, 9);
		VERIFY(r == 10);
		const int v2[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

struct Point
{
	int x;
	int y;
};

HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

HAMON_CXX11_CONSTEXPR bool
operator!=(Point const& lhs, Point const& rhs)
{
	return !(lhs == rhs);
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::inplace_vector<Point, 10> v
	{
		Point{1,2},
		Point{2,3},
		Point{1,3},
		Point{1,2},
		Point{3,2},
	};
	auto r = hamon::erase(v, {1,2});	// 型名は省略できる
	VERIFY(r == 2);
	Point const v2[]
	{
		Point{2,3},
		Point{1,3},
		Point{3,2},
	};
	VERIFY(hamon::ranges::equal(v, v2));
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	{
		hamon::inplace_vector<int, 5> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {3,1,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::inplace_vector<int, 20> v = {3,1,4,1,5,9,2,6,5,3,5};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 5);
		const int v2[] = {3,1,4,1,2,3};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, ErasureTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
#if defined(HAMON_MSVC) && (HAMON_MSVC < 1930)
	EXPECT_TRUE(test2());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
#endif
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/erase2
	{
		auto print = [](hamon::inplace_vector<int, 10> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<int, 10> v(10, 0);
		hamon::iota(v.begin(), v.end(), 0);
		EXPECT_EQ("0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ", print(v));

		auto erased = hamon::erase(v, 3);
		EXPECT_EQ("0, 1, 2, 4, 5, 6, 7, 8, 9, ", print(v));
		EXPECT_TRUE(erased == 1);

		erased = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		EXPECT_EQ("1, 5, 7, 9, ", print(v));
		EXPECT_TRUE(erased == 5);

		hamon::inplace_vector<hamon::complex<double>, 10> nums {{2, 2}, {4, 2}, {4, 8}, {4, 2}};
		hamon::erase(nums, {4, 2}); // since U = T, the value type can be ommited
		{
			std::stringstream ss;
			for (auto const& e : nums)
			{
				ss << e << ", ";
			}
			EXPECT_EQ("(2,2), (4,8), ", ss.str());
		}
	}
}

}	// namespace erasure_test

}	// namespace hamon_inplace_vector_test
