/**
 *	@file	unit_test_ranges_slide_view_iterator_add_assign.cpp
 *
 *	@brief	operator+= のテスト
 *
 *	constexpr iterator& operator+=(difference_type x)
 *	  requires random_access_range<Base>;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
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
namespace iterator_add_assign_test
{

template <typename T, typename Iterator, typename Sentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR Iterator begin() const noexcept { return Iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel end()         noexcept { return Sentinel{}; }
	HAMON_CXX11_CONSTEXPR Sentinel end()   const noexcept { return Sentinel{}; }
};

template <typename T>
using TestUnreachableView = TestView<int, random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>;

template <typename T, typename = void>
struct has_add_assign
	: public hamon::false_type {};

template <typename T>
struct has_add_assign<T, hamon::void_t<decltype(hamon::declval<T>() += hamon::declval<int>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(!has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
	}
	{
		using V = TestUnreachableView<int>;
		using SV = hamon::ranges::slide_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert( has_add_assign<I&>::value, "");
		static_assert(!has_add_assign<I const&>::value, "");
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
		static_assert(hamon::is_same<decltype(hamon::declval<I&>() += hamon::declval<int>()), I&>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		SV sv{v, 2};

		auto it = sv.begin();
		{
			int const expected[] = {1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t1 = it += 2;
		VERIFY(&t1 == &it);
		{
			int const expected[] = {3,4};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewIteratorAddAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<TestUnreachableView>());
}

}	// namespace iterator_add_assign_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
