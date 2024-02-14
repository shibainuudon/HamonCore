/**
 *	@file	unit_test_ranges_zip_view_iterator_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr auto operator[](difference_type n) const
 *	  requires all-random-access<Const, Views...>;
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_subscript_test
{

template <typename T, typename = void>
struct has_subscript
	: public hamon::false_type {};

template <typename T>
struct has_subscript<T, hamon::void_t<decltype(hamon::declval<T>()[hamon::declval<int>()])>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), hamon::tuple<int&>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), hamon::tuple<int&>>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), hamon::tuple<int&>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), hamon::tuple<int&>>::value, "");
	}
	{
		using V1 = test_random_access_view<float>;
		using V2 = test_random_access_view<int const>;
		using V3 = test_random_access_view<char>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_subscript<I&>::value, "");
		static_assert( has_subscript<I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I&      >()[hamon::declval<int>()]), hamon::tuple<float&, int const&, char&>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>()[hamon::declval<int>()]), hamon::tuple<float&, int const&, char&>>::value, "");
	}
	{
		using V1 = test_bidirectional_view<float>;
		using V2 = test_random_access_view<int const>;
		using V3 = test_random_access_view<char>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<float>;
		using V2 = test_bidirectional_view<int const>;
		using V3 = test_random_access_view<char>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<float>;
		using V2 = test_random_access_view<int const>;
		using V3 = test_bidirectional_view<char>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_subscript<I&>::value, "");
		static_assert(!has_subscript<I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using ZV = hamon::ranges::zip_view<V1, V2>;

	int a1[] = {0,1,2,3,4};
	char a2[] = {10,20,30};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);
	auto it = zv.begin();
	auto t0 = it[0];
	auto t1 = it[1];
	auto t2 = it[2];
	VERIFY(hamon::adl_get<0>(t0) == 0);
	VERIFY(hamon::adl_get<1>(t0) == 10);
	VERIFY(hamon::adl_get<0>(t1) == 1);
	VERIFY(hamon::adl_get<1>(t1) == 20);
	VERIFY(hamon::adl_get<0>(t2) == 2);
	VERIFY(hamon::adl_get<1>(t2) == 30);

	hamon::adl_get<0>(t0) = -1;
	hamon::adl_get<1>(t1) = 42;

	VERIFY(a1[0] == -1);
	VERIFY(a1[1] == 1);
	VERIFY(a1[2] == 2);
	VERIFY(a1[3] == 3);
	VERIFY(a1[4] == 4);

	VERIFY(a2[0] == 10);
	VERIFY(a2[1] == 42);
	VERIFY(a2[2] == 30);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewIteratorSubscriptTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_subscript_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
