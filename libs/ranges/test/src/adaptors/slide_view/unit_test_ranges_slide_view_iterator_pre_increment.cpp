/**
 *	@file	unit_test_ranges_slide_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
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
namespace iterator_pre_increment_test
{

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = View<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_pre_increment<I&>::value, "");
		static_assert(!has_pre_increment<I const&>::value, "");
		static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		SV sv{v, 3};

		auto it = sv.begin();
		{
			int const expected[] = {1,2,3};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t1 = ++it;
		VERIFY(&t1 == &it);
		{
			int const expected[] = {2,3,4};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t2 = ++it;
		VERIFY(&t2 == &it);
		{
			int const expected[] = {3,4,5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		VERIFY(it != sv.end());
		VERIFY(++it == sv.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
}

}	// namespace iterator_pre_increment_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
