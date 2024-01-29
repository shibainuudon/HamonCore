/**
 *	@file	unit_test_ranges_join_with_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end();
 *	constexpr auto end() const;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace end_test
{

template <typename T>
struct ValueForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX11_CONSTEXPR ValueForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ValueForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ValueForwardIterator(ValueForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ValueForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueForwardIterator& rhs) const { return !(*this == rhs); }
};

template <
	typename T,
	typename Iterator,
	typename ConstIterator,
	typename Sentinel = test_sentinel<Iterator>,
	typename ConstSentinel = test_sentinel<ConstIterator>
>
struct NotSimpleView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using sentinel = Sentinel;
	using const_sentinel = ConstSentinel;

	HAMON_CXX11_CONSTEXPR NotSimpleView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleView(T (&arr)[N]) : NotSimpleView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
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
	// is_reference_v<InnerRng> &&
	// forward_range<V> &&
	// forward_range<InnerRng> &&
	// common_range<V> &&
	// common_range<InnerRng>
	{
		// simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::iterator<true>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::iterator<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// !simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::iterator<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::iterator<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// simple_view<V> &&
		// !simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::iterator<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::iterator<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	// !is_reference_v<InnerRng> &&
	// forward_range<V> &&
	// forward_range<InnerRng> &&
	// common_range<V> &&
	// common_range<InnerRng>
	{
		// simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(!hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert(!has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// !simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV const>,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV const>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(!hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert(!has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// simple_view<V> &&
		// !simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV>,
				ValueForwardIterator<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(!hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert(!has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	// is_reference_v<InnerRng> &&
	// !forward_range<V> &&
	// forward_range<InnerRng> &&
	// common_range<V> &&
	// common_range<InnerRng>
	{
		// simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(!hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert(!has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// !simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV const>,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV const>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(!hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert(!has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// simple_view<V> &&
		// !simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV>,
				input_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(!hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert(!has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	// is_reference_v<InnerRng> &&
	// forward_range<V> &&
	// !forward_range<InnerRng> &&
	// common_range<V> &&
	// common_range<InnerRng>
	{
		// simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(!hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<true>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// !simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(!hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// simple_view<V> &&
		// !simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(!hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	// is_reference_v<InnerRng> &&
	// forward_range<V> &&
	// forward_range<InnerRng> &&
	// !common_range<V> &&
	// common_range<InnerRng>
	{
		// simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<true>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// !simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// simple_view<V> &&
		// !simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::common_range_t<V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	// is_reference_v<InnerRng> &&
	// forward_range<V> &&
	// forward_range<InnerRng> &&
	// common_range<V> &&
	// !common_range<InnerRng>
	{
		// simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<true>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// !simple_view<V> &&
		// simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV const>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}

		// simple_view<V> &&
		// !simple_view<Pattern>
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerRng = hamon::ranges::range_reference_t<V>;

			static_assert(hamon::is_reference<InnerRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<V>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::common_range_t<V>::value, "");
			static_assert(!hamon::ranges::common_range_t<InnerRng>::value, "");
			static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
			static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert( has_end<RV&>::value, "");
			static_assert( has_end<RV const&>::value, "");

			//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().end()), typename RV::sentinel<false>>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// forward_range<const V> &&
	// forward_range<const Pattern> &&
	// is_reference_v<InnerConstRng> &&
	// input_range<InnerConstRng>
	{
		// forward_range<InnerConstRng> &&
		// common_range<const V> &&
		// common_range<InnerConstRng>)
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerConstRng = hamon::ranges::range_reference_t<const V>;

			static_assert(hamon::ranges::forward_range_t<V const>::value, "");
			static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
			static_assert(hamon::is_reference<InnerConstRng>::value, "");
			static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerConstRng>::value, "");
			static_assert(hamon::ranges::common_range_t<const V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerConstRng>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert(has_end<RV const&>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::iterator<true>>::value, "");
			
			RV const rv {};
			auto it = rv.end();
			(void)it;
		}

		// !forward_range<InnerConstRng> &&
		// common_range<const V> &&
		// common_range<InnerConstRng>)
		{
			using IV = NotSimpleView<int,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>,
				input_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerConstRng = hamon::ranges::range_reference_t<const V>;

			static_assert(hamon::ranges::forward_range_t<V const>::value, "");
			static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
			static_assert(hamon::is_reference<InnerConstRng>::value, "");
			static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");
			static_assert(!hamon::ranges::forward_range_t<InnerConstRng>::value, "");
			static_assert(hamon::ranges::common_range_t<const V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerConstRng>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert(has_end<RV const&>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV const rv {};
			auto it = rv.end();
			(void)it;
		}

		// forward_range<InnerConstRng> &&
		// !common_range<const V> &&
		// common_range<InnerConstRng>)
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerConstRng = hamon::ranges::range_reference_t<const V>;

			static_assert(hamon::ranges::forward_range_t<V const>::value, "");
			static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
			static_assert(hamon::is_reference<InnerConstRng>::value, "");
			static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerConstRng>::value, "");
			static_assert(!hamon::ranges::common_range_t<const V>::value, "");
			static_assert(hamon::ranges::common_range_t<InnerConstRng>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert(has_end<RV const&>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV const rv {};
			auto it = rv.end();
			(void)it;
		}

		// forward_range<InnerConstRng> &&
		// common_range<const V> &&
		// !common_range<InnerConstRng>)
		{
			using IV = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int>>;
			using V = NotSimpleView<IV,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>,
				forward_iterator_wrapper<IV>>;
			using Pattern = NotSimpleView<int,
				forward_iterator_wrapper<int>,
				forward_iterator_wrapper<int const>>;
			using InnerConstRng = hamon::ranges::range_reference_t<const V>;

			static_assert(hamon::ranges::forward_range_t<V const>::value, "");
			static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
			static_assert(hamon::is_reference<InnerConstRng>::value, "");
			static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");
			static_assert(hamon::ranges::forward_range_t<InnerConstRng>::value, "");
			static_assert(hamon::ranges::common_range_t<const V>::value, "");
			static_assert(!hamon::ranges::common_range_t<InnerConstRng>::value, "");

			using RV = hamon::ranges::join_with_view<V, Pattern>;
			static_assert(has_end<RV const&>::value, "");
			//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().end()), typename RV::sentinel<true>>::value, "");

			RV const rv {};
			auto it = rv.end();
			(void)it;
		}
	}

	// !forward_range<const V> &&
	// forward_range<const Pattern> &&
	// is_reference_v<InnerConstRng> &&
	// input_range<InnerConstRng>
	{
		using IV = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using V = NotSimpleView<IV,
			input_iterator_wrapper<IV>,
			input_iterator_wrapper<IV>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert(hamon::is_reference<InnerConstRng>::value, "");
		static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_end<RV&>::value, "");
		static_assert(!has_end<RV const&>::value, "");
	}

	// forward_range<const V> &&
	// !forward_range<const Pattern> &&
	// is_reference_v<InnerConstRng> &&
	// input_range<InnerConstRng>
	{
		using IV = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using V = NotSimpleView<IV,
			forward_iterator_wrapper<IV>,
			forward_iterator_wrapper<IV>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(!hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert(hamon::is_reference<InnerConstRng>::value, "");
		static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_end<RV&>::value, "");
		static_assert(!has_end<RV const&>::value, "");
	}

	// forward_range<const V> &&
	// forward_range<const Pattern> &&
	// !is_reference_v<InnerConstRng> &&
	// input_range<InnerConstRng>
	{
		using IV = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using V = NotSimpleView<IV,
			ValueForwardIterator<IV>,
			ValueForwardIterator<IV>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert(!hamon::is_reference<InnerConstRng>::value, "");
		static_assert(hamon::ranges::input_range_t<InnerConstRng>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_end<RV&>::value, "");
		static_assert(!has_end<RV const&>::value, "");
	}

	// forward_range<const V> &&
	// forward_range<const Pattern> &&
	// is_reference_v<InnerConstRng> &&
	// !input_range<InnerConstRng>
	{
		using IV = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			output_iterator_wrapper<int>>;
		using V = NotSimpleView<IV,
			forward_iterator_wrapper<IV>,
			forward_iterator_wrapper<IV const>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert(hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert(hamon::is_reference<InnerConstRng>::value, "");
		static_assert(!hamon::ranges::input_range_t<InnerConstRng>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_end<RV&>::value, "");
		static_assert(!has_end<RV const&>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace end_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
