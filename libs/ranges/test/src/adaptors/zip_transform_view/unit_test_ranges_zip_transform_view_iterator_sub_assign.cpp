/**
 *	@file	unit_test_ranges_zip_transform_view_iterator_sub_assign.cpp
 *
 *	@brief	operator-= のテスト
 *
 *	constexpr iterator& operator-=(difference_type x) requires random_access_range<Base>;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace iterator_sub_assign_test
{

struct F1
{
	int operator()(int) const;
};

struct Add
{
	constexpr int operator()(int x, char y) const { return x + y; }
};

template <typename T, typename = void>
struct has_sub_assign
	: public hamon::false_type {};

template <typename T>
struct has_sub_assign<T, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<int>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<char>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() -= hamon::declval<int>()), I&>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<char>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<char>;
		using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_sub_assign<I&>::value, "");
		static_assert(!has_sub_assign<I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using F = Add;
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

	F f{};
	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(f, v1, v2);
	auto it = zv.begin();
	++it;
	++it;
	VERIFY(*it == 47);
	auto t1 = (it -= 2);
	VERIFY(t1 == it);
	VERIFY(*it == 43);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewIteratorSubAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_sub_assign_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
