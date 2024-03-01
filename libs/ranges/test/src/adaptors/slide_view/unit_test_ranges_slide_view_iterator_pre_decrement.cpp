/**
 *	@file	unit_test_ranges_slide_view_iterator_pre_decrement.cpp
 *
 *	@brief	前置デクリメントのテスト
 *
 *	constexpr iterator& operator--() requires bidirectional_range<Base>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace iterator_pre_decrement_test
{

template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_pre_decrement<I&>::value, "");
		static_assert(!has_pre_decrement<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_pre_decrement<I&>::value, "");
		static_assert(!has_pre_decrement<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_pre_decrement<I&>::value, "");
		static_assert(!has_pre_decrement<I const&>::value, "");
	}
	return true;
}

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = View<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<decltype(--hamon::declval<I&>()), I&>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		SV sv{v, 3};

		auto it = sv.begin();
		++it;
		++it;
		{
			int const expected[] = {3,4,5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t1 = --it;
		VERIFY(&t1 == &it);
		{
			int const expected[] = {2,3,4};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t2 = --it;
		VERIFY(&t2 == &it);
		{
			int const expected[] = {1,2,3};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		VERIFY(it == sv.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewIteratorPreDecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_random_access_view>());
}

}	// namespace iterator_pre_decrement_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
