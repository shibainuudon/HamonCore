/**
 *	@file	unit_test_ranges_adjacent_transform_view_sentinel_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	template<bool OtherConst>
 *	  requires sized_sentinel_for<inner-sentinel<Const>, inner-iterator<OtherConst>>
 *	friend constexpr range_difference_t<maybe-const<OtherConst, InnerView>>
 *	operator-(const iterator<OtherConst>& x, const sentinel& y);
 *
 *	template<bool OtherConst>
 *	  requires sized_sentinel_for<inner-sentinel<Const>, inner-iterator<OtherConst>>
 *	friend constexpr range_difference_t<maybe-const<OtherConst, InnerView>>
 *	operator-(const sentinel& x, const iterator<OtherConst>& y);
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
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
namespace sentinel_sub_test
{

struct F
{
	constexpr int operator()(int x, int y) const { return x + y; }
	constexpr int operator()(int x, int y, int z) const { return x + y + z; }
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
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{Iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{ConstIterator{m_last}}; }
};

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// Microsoft-STL の operator-(iterator, sentinel) はエラーになってしまう
#if !(defined(HAMON_USE_STD_RANGES_ADJACENT_TRANSFORM_VIEW) && defined(HAMON_STDLIB_DINKUMWARE))

	// iterator<true>, sentinel<true>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV const&>().begin());
		using S = decltype(hamon::declval<AV const&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<true>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV const&>().begin());
		using S = decltype(hamon::declval<AV const&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<true>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v, F{}};
		AV const& cav = av;
		I i = cav.begin();
		S s = cav.end();
		VERIFY(i - s == -3);
		VERIFY(s - i ==  3);
	}

	// iterator<false>, sentinel<true>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int const>,
			test_sentinel<forward_iterator_wrapper<int const>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV&>().begin());
		using S = decltype(hamon::declval<AV const&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<true>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV&>().begin());
		using S = decltype(hamon::declval<AV const&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<true>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v, F{}};
		AV const& cav = av;
		I i = av.begin();
		S s = cav.end();
		VERIFY(i - s == -3);
		VERIFY(s - i ==  3);
	}

	// iterator<true>, sentinel<false>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int const>,
			test_sentinel<forward_iterator_wrapper<int const>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV const&>().begin());
		using S = decltype(hamon::declval<AV&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<false>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 3>;

		using I = decltype(hamon::declval<AV const&>().begin());
		using S = decltype(hamon::declval<AV&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<false>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v, F{}};
		AV const& cav = av;
		I i = cav.begin();
		S s = av.end();
		VERIFY(i - s == -2);
		VERIFY(s - i ==  2);
	}

	// iterator<false>, sentinel<false>
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int const>,
			test_sentinel<forward_iterator_wrapper<int const>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV&>().begin());
		using S = decltype(hamon::declval<AV&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<false>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>,
			random_access_iterator_wrapper<int>,
			test_sentinel<random_access_iterator_wrapper<int>>
		>;
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

		using I = decltype(hamon::declval<AV&>().begin());
		using S = decltype(hamon::declval<AV&>().end());
		//static_assert(hamon::is_same<I, AV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, AV::sentinel<false>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a[] = {1,2,3,4,5};
		V v(a);
		AV av{v, F{}};
		I i = av.begin();
		S s = av.end();
		VERIFY(i - s == -4);
		VERIFY(s - i ==  4);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewSentinelSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_sub_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
