/**
 *	@file	unit_test_ranges_join_with_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin();
 *	constexpr auto begin() const;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
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
namespace begin_test
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
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// not forward_range<V>
	{
		using V = test_input_view<test_input_view<int>>;
		using Pattern = test_forward_view<int>;
		static_assert(!hamon::ranges::forward_range_t<V>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<false>>::value, "");

		RV rv{};
		auto it = rv.begin();
		(void)it;
	}

	// forward_range<V> && use_const
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(hamon::is_reference<hamon::ranges::range_reference_t<V>>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::iterator<true>>::value, "");

		RV rv{};
		auto it = rv.begin();
		(void)it;
	}

	// forward_range<V> && !simple_view<V>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView const>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(!hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(hamon::is_reference<hamon::ranges::range_reference_t<V>>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::iterator<true>>::value, "");

		RV rv{};
		auto it = rv.begin();
		(void)it;
	}

	// forward_range<V> && !hamon::is_reference_v<InnerRng>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			ValueForwardIterator<InnerView>,
			ValueForwardIterator<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(!hamon::is_reference<hamon::ranges::range_reference_t<V>>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<Pattern>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<false>>::value, "");

		RV rv{};
		auto it = rv.begin();
		(void)it;
	}

	// forward_range<V> && !hamon::ranges::detail::simple_view<Pattern>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;
		static_assert(hamon::ranges::forward_range_t<V>::value, "");
		static_assert(hamon::ranges::detail::simple_view_t<V>::value, "");
		static_assert(hamon::is_reference<hamon::ranges::range_reference_t<V>>::value, "");
		static_assert(!hamon::ranges::detail::simple_view_t<Pattern>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::iterator<true>>::value, "");

		RV rv{};
		auto it = rv.begin();
		(void)it;
	}
	
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// forward_range<V const> &&
	// forward_range<Pattern const> &&
	// is_reference_v<range_reference_t<V const>> &&
	// input_range<range_reference_t<V const>>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;

		static_assert( hamon::ranges::forward_range_t<V const>::value, "");
		static_assert( hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert( hamon::is_reference<hamon::ranges::range_reference_t<V const>>::value, "");
		static_assert( hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V const>>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		static_assert( has_begin<RV&>::value, "");
		static_assert( has_begin<RV const&>::value, "");

		//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::iterator<true>>::value, "");

		RV const rv{};
		auto it = rv.begin();
		(void)it;
	}

	// !forward_range<V const>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			input_iterator_wrapper<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;

		static_assert(!hamon::ranges::forward_range_t<V const>::value, "");
		static_assert( hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert( hamon::is_reference<hamon::ranges::range_reference_t<V const>>::value, "");
		static_assert( hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V const>>::value, "");

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");
	}

	// forward_range<V const> && !forward_range<Pattern const>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			input_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;

		static_assert( hamon::ranges::forward_range_t<V const>::value, "");
		static_assert(!hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert( hamon::is_reference<hamon::ranges::range_reference_t<V const>>::value, "");
		static_assert( hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V const>>::value, "");

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");
	}

	// forward_range<V const> && !is_reference_v<range_reference_t<V const>>
	{
		using InnerView = test_input_view<int>;
		using V = NotSimpleView<InnerView,
			ValueForwardIterator<InnerView>,
			ValueForwardIterator<InnerView>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;

		static_assert( hamon::ranges::forward_range_t<V const>::value, "");
		static_assert( hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert(!hamon::is_reference<hamon::ranges::range_reference_t<V const>>::value, "");
		static_assert( hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V const>>::value, "");

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");
	}

	// forward_range<V const> && !input_range<range_reference_t<V const>>
	{
		using InnerView = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			output_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			test_sentinel<output_iterator_wrapper<int>>>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView const>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;

		static_assert( hamon::ranges::forward_range_t<V const>::value, "");
		static_assert( hamon::ranges::forward_range_t<Pattern const>::value, "");
		static_assert( hamon::is_reference<hamon::ranges::range_reference_t<V const>>::value, "");
		static_assert(!hamon::ranges::input_range_t<hamon::ranges::range_reference_t<V const>>::value, "");

		static_assert( has_begin<RV&>::value, "");
		static_assert(!has_begin<RV const&>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace begin_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
