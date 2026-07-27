/**
 *	@file	unit_test_ranges_as_input_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin() requires (!simple-view<V>);
 *	constexpr auto begin() const requires range<const V>;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace begin_test
{

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// !simple-view<V> && range<const V>
	using V = TestView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int const>,
		forward_iterator_wrapper<int const>
	>;

	static_assert(!hamon::ranges::detail::simple_view<V>, "");
	static_assert( hamon::ranges::range<V const>, "");

	using AIV = hamon::ranges::as_input_view<V>;
	static_assert( has_begin<AIV&>::value, "");
	static_assert( has_begin<AIV const&>::value, "");
	static_assert( has_cbegin<AIV&>::value, "");
	static_assert( has_cbegin<AIV const&>::value, "");

	using I  = decltype(hamon::declval<AIV&>().begin());
	using CI = decltype(hamon::declval<AIV const&>().begin());
	static_assert(!hamon::is_same<I, CI>::value, "");
	static_assert(!hamon::is_same<I,  decltype(hamon::declval<V&>().begin())>::value, "");
	static_assert(!hamon::is_same<CI, decltype(hamon::declval<V const&>().begin())>::value, "");

	int a[] = { 1,2,3 };
	V v(a);
	{
		AIV aiv(v);
		auto it = aiv.begin();
		VERIFY(*it == 1);
	}
	{
		AIV const aiv(v);
		auto it = aiv.begin();
		VERIFY(*it == 1);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// !simple-view<V> && !range<const V>
	using V = TestView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int const>,
		forward_iterator_wrapper<int>
	>;

	static_assert(!hamon::ranges::detail::simple_view<V>, "");
	static_assert(!hamon::ranges::range<V const>, "");

	using AIV = hamon::ranges::as_input_view<V>;
	static_assert( has_begin<AIV&>::value, "");
	static_assert(!has_begin<AIV const&>::value, "");
	static_assert( has_cbegin<AIV&>::value, "");
	static_assert(!has_cbegin<AIV const&>::value, "");

	using I  = decltype(hamon::declval<AIV&>().begin());
	static_assert(!hamon::is_same<I,  decltype(hamon::declval<V&>().begin())>::value, "");

	int a[] = { 1,2,3 };
	V v(a);
	{
		AIV aiv(v);
		auto it = aiv.begin();
		VERIFY(*it == 1);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// simple-view<V> && range<const V>
	using V = TestView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>
	>;

	static_assert( hamon::ranges::detail::simple_view<V>, "");
	static_assert( hamon::ranges::range<V const>, "");

	using AIV = hamon::ranges::as_input_view<V>;
	static_assert( has_begin<AIV&>::value, "");
	static_assert( has_begin<AIV const&>::value, "");
	static_assert( has_cbegin<AIV&>::value, "");
	static_assert( has_cbegin<AIV const&>::value, "");

	using I  = decltype(hamon::declval<AIV&>().begin());
	using CI = decltype(hamon::declval<AIV const&>().begin());
	static_assert( hamon::is_same<I, CI>::value, "");
	static_assert(!hamon::is_same<I,  decltype(hamon::declval<V&>().begin())>::value, "");
	static_assert(!hamon::is_same<CI, decltype(hamon::declval<V const&>().begin())>::value, "");

	int a[] = { 1,2,3 };
	V v(a);
	{
		AIV aiv(v);
		auto it = aiv.begin();
		VERIFY(*it == 1);
	}
	{
		AIV const aiv(v);
		auto it = aiv.begin();
		VERIFY(*it == 1);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// simple-view<V> && !range<const V>
	// この条件を満たすことはできない
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace begin_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
