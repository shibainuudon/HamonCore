/**
 *	@file	unit_test_ranges_zip_view_iterator_add.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	friend constexpr iterator operator+(const iterator& i, difference_type n)
 *	  requires all-random-access<Const, Views...>;
 *	friend constexpr iterator operator+(difference_type n, const iterator& i)
 *	  requires all-random-access<Const, Views...>;
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_add_test
{

template <typename T, typename U, typename = void>
struct has_add
	: public hamon::false_type {};

template <typename T, typename U>
struct has_add<T, U, hamon::void_t<decltype(hamon::declval<T>() + hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using ZV = hamon::ranges::zip_view<V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert( has_add<I const&, int>::value, "");
		static_assert( has_add<int, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() + hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<int>() + hamon::declval<I const&>()), I>::value, "");
	}
	{
		using V1 = test_bidirectional_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<int>;
		using V3 = test_random_access_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using V3 = test_bidirectional_view<int>;
		using ZV = hamon::ranges::zip_view<V1, V2, V3>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(!has_add<I const&, int>::value, "");
		static_assert(!has_add<int, I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using ZV = hamon::ranges::zip_view<V1, V2>;

	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);

	auto it1 = zv.begin() + 1;
	auto it2 = 2 + zv.begin();
	VERIFY(hamon::adl_get<0>(*it1) == 43);
	VERIFY(hamon::adl_get<1>(*it1) == 2);
	VERIFY(hamon::adl_get<0>(*it2) == 44);
	VERIFY(hamon::adl_get<1>(*it2) == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewIteratorAddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_add_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
