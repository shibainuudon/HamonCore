/**
 *	@file	unit_test_ranges_as_input_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!simple-view<V>);
 *	constexpr auto end() const requires range<const V>;
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
namespace end_test
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
	static_assert( has_end<AIV&>::value, "");
	static_assert( has_end<AIV const&>::value, "");
	static_assert( has_cend<AIV&>::value, "");
	static_assert( has_cend<AIV const&>::value, "");

	using S  = decltype(hamon::declval<AIV&>().end());
	using CS = decltype(hamon::declval<AIV const&>().end());
	static_assert(!hamon::is_same<S, CS>::value, "");
	static_assert( hamon::is_same<S,  decltype(hamon::declval<V&>().end())>::value, "");
	static_assert( hamon::is_same<CS, decltype(hamon::declval<V const&>().end())>::value, "");

	int a[] = { 1,2,3 };
	V v(a);
	{
		AIV aiv(v);
		auto sent = aiv.end();
		VERIFY(sent != aiv.begin());
	}
	{
		AIV const aiv(v);
		auto sent = aiv.end();
		VERIFY(sent != aiv.begin());
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
	static_assert( has_end<AIV&>::value, "");
	static_assert(!has_end<AIV const&>::value, "");
	static_assert( has_cend<AIV&>::value, "");
	static_assert(!has_cend<AIV const&>::value, "");

	using S  = decltype(hamon::declval<AIV&>().end());
	static_assert( hamon::is_same<S,  decltype(hamon::declval<V&>().end())>::value, "");

	int a[] = { 1,2,3 };
	V v(a);
	{
		AIV aiv(v);
		auto sent = aiv.end();
		VERIFY(sent != aiv.begin());
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
	static_assert( has_end<AIV&>::value, "");
	static_assert( has_end<AIV const&>::value, "");
	static_assert( has_cend<AIV&>::value, "");
	static_assert( has_cend<AIV const&>::value, "");

	using S  = decltype(hamon::declval<AIV&>().end());
	using CS = decltype(hamon::declval<AIV const&>().end());
	static_assert( hamon::is_same<S, CS>::value, "");
	static_assert( hamon::is_same<S,  decltype(hamon::declval<V&>().end())>::value, "");
	static_assert( hamon::is_same<CS, decltype(hamon::declval<V const&>().end())>::value, "");

	int a[] = { 1,2,3 };
	V v(a);
	{
		AIV aiv(v);
		auto sent = aiv.end();
		VERIFY(sent != aiv.begin());
	}
	{
		AIV const aiv(v);
		auto sent = aiv.end();
		VERIFY(sent != aiv.begin());
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

GTEST_TEST(RangesTest, AsInputViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace end_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
