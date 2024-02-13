/**
 *	@file	unit_test_ranges_enumerate_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end() requires (!simple-view<V>);
 *	constexpr auto end() const requires range-with-movable-references<const V>;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
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

template <typename T, typename Reference, typename IterMoveResult>
struct TestForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR Reference            operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestForwardIterator& rhs) const { return !(*this == rhs); }

	friend IterMoveResult iter_move(TestForwardIterator const& it) { return *it.m_ptr; }
};

template <typename T, typename Reference, typename IterMoveResult>
struct TestRandomAccessIterator
{
	T*	m_ptr;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestRandomAccessIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestRandomAccessIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestRandomAccessIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR TestRandomAccessIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR TestRandomAccessIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestRandomAccessIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestRandomAccessIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR TestRandomAccessIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type           operator-(TestRandomAccessIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR Reference                 operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                        operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestRandomAccessIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestRandomAccessIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const TestRandomAccessIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const TestRandomAccessIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const TestRandomAccessIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const TestRandomAccessIterator& rhs) const { return m_ptr >= rhs.m_ptr; }

	friend HAMON_CXX14_CONSTEXPR TestRandomAccessIterator
	operator+(hamon::ptrdiff_t n, TestRandomAccessIterator const& it) { return it + n; }

	friend IterMoveResult iter_move(TestRandomAccessIterator const& it) { return *it.m_ptr; }
};

struct NotMovable
{
	NotMovable(NotMovable const&) = default;
	NotMovable(NotMovable&&) = delete;
};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// simple_view<V> &&
	// range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert( (hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert( (hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<CS, EV::iterator<true>>::value, "");
	}

	// !simple_view<V> &&
	// range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int const>,
			random_access_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert( (hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert( (hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::iterator<true>>::value, "");
	}

	// simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		// simple_view<V> && !range_with_movable_references<V const> ということは、
		// range_with_movable_references<V> も false になってしまうので
		// インスタンス化できない
	}

	// !simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		using V = TestView<NotMovable,
			TestRandomAccessIterator<NotMovable, NotMovable&, NotMovable&>,
			TestRandomAccessIterator<NotMovable, NotMovable&, NotMovable&>,
			TestRandomAccessIterator<NotMovable, NotMovable, NotMovable>,
			TestRandomAccessIterator<NotMovable, NotMovable, NotMovable>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert(!hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert( (hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert( (hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert(!has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<false>>::value, "");
	}

	// simple_view<V> &&
	// range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		// simple_view<V> の場合、
		// common_range<V> == common_range<V const>
		// sized_range<V> == sized_range<V const>
		// になるので条件を満たさない
	}

	// !simple_view<V> &&
	// range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert(!(hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert( (hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::iterator<true>>::value, "");
	}

	// simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		// simple_view<V> && !range_with_movable_references<V const> ということは、
		// range_with_movable_references<V> も false になってしまうので
		// インスタンス化できない
	}

	// !simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// (common_range<V const> && sized_range<V const>)
	{
		using V = TestView<NotMovable,
			TestForwardIterator<NotMovable, NotMovable&, NotMovable&>,
			TestForwardIterator<NotMovable, NotMovable&, NotMovable&>,
			TestRandomAccessIterator<NotMovable, NotMovable, NotMovable>,
			TestRandomAccessIterator<NotMovable, NotMovable, NotMovable>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert(!hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert(!(hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert( (hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert(!has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<false>>::value, "");
	}

	// simple_view<V> &&
	// range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		// simple_view<V> の場合、
		// common_range<V> == common_range<V const>
		// sized_range<V> == sized_range<V const>
		// になるので条件を満たさない
	}

	// !simple_view<V> &&
	// range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert( (hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert(!(hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::sentinel<true>>::value, "");
	}

	// simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		// simple_view<V> && !range_with_movable_references<V const> ということは、
		// range_with_movable_references<V> も false になってしまうので
		// インスタンス化できない
	}

	// !simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// (common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int const>,
			random_access_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert(!hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert( (hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert(!(hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert(!has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//static_assert(hamon::is_same<S,  EV::iterator<false>>::value, "");
	}

	// simple_view<V> &&
	// range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>
		>;
		static_assert( hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert(!(hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert(!(hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<true>>::value, "");
		//static_assert(hamon::is_same<CS, EV::sentinel<true>>::value, "");
	}

	// !simple_view<V> &&
	// range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int const>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert( hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert(!(hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert(!(hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert( has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//using CS = decltype(hamon::declval<EV const&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<false>>::value, "");
		//static_assert(hamon::is_same<CS, EV::sentinel<true>>::value, "");
	}

	// simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		// simple_view<V> && !range_with_movable_references<V const> ということは、
		// range_with_movable_references<V> も false になってしまうので
		// インスタンス化できない
	}

	// !simple_view<V> &&
	// !range_with_movable_references<V const> &&
	// !(common_range<V> && sized_range<V>)
	// !(common_range<V const> && sized_range<V const>)
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int>
		>;
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		//static_assert(!hamon::ranges::detail::range_with_movable_references<V const>, "");
		static_assert(!(hamon::ranges::common_range_t<V>::value && hamon::ranges::sized_range_t<V>::value), "");
		static_assert(!(hamon::ranges::common_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

		using EV = hamon::ranges::enumerate_view<V>;
		static_assert( has_end<EV&>::value, "");
		static_assert(!has_end<EV const&>::value, "");

		//using S  = decltype(hamon::declval<EV&>().end());
		//static_assert(hamon::is_same<S,  EV::sentinel<false>>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int const>,
			random_access_iterator_wrapper<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;

		int a[] = {1, 2, 3};
		V v(a);
		{
			EV ev(v);
			auto it = ev.end();
			(void)it;
		}
		{
			EV const ev(v);
			auto it = ev.end();
			(void)it;
		}
	}
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>,
			forward_iterator_wrapper<int const>
		>;
		using EV = hamon::ranges::enumerate_view<V>;

		int a[] = {1, 2, 3};
		V v(a);
		{
			EV ev(v);
			auto it = ev.end();
			(void)it;
		}
		{
			EV const ev(v);
			auto it = ev.end();
			(void)it;
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace end_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
