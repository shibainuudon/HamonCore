/**
 *	@file	unit_test_ranges_adjacent_transform_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin();
 *	constexpr auto begin() const
 *	  requires range<const InnerView> &&
 *	    regular_invocable<const F&, REPEAT(range_reference_t<const V>, N)...>;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace begin_test
{

struct F1
{
	HAMON_CXX11_CONSTEXPR int operator()(int x, int y) const { return x + y; }
};

struct F2
{
	HAMON_CXX14_CONSTEXPR int operator()(int x, int y) { return x + y; }
};

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		static_assert( has_begin<AV&>::value, "");
		static_assert( has_begin<AV const&>::value, "");

		using I  = decltype(hamon::declval<AV&>().begin());
		using CI = decltype(hamon::declval<AV const&>().begin());
		//static_assert(hamon::is_same<I,  AV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, AV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		F1 f;
		{
			AV av(v, f);
			auto it = av.begin();
			VERIFY(*it == 3);
		}
		{
			AV const av(v, f);
			auto it = av.begin();
			VERIFY(*it == 3);
		}
	}

	// !range<InnerView const>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 2>;
		static_assert( has_begin<AV&>::value, "");
		static_assert(!has_begin<AV const&>::value, "");

		//using I  = decltype(hamon::declval<AV&>().begin());
		//static_assert(hamon::is_same<I,  AV::iterator<false>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		F1 f;
		{
			AV av(v, f);
			auto it = av.begin();
			VERIFY(*it == 3);
		}
	}

	// !regular_invocable<const F&, REPEAT(range_reference_t<const V>, N)...>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 2>;
		static_assert( has_begin<AV&>::value, "");
		static_assert(!has_begin<AV const&>::value, "");

		//using I  = decltype(hamon::declval<AV&>().begin());
		//static_assert(hamon::is_same<I,  AV::iterator<false>>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		F2 f;
		{
			AV av(v, f);
			auto it = av.begin();
			VERIFY(*it == 3);
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
