/**
 *	@file	unit_test_ranges_drop_view.cpp
 *
 *	@brief	ranges::drop_view のテスト
 */

#include <hamon/ranges/adaptors/drop_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/take_view.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/span.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace drop_view_test
{

template <typename T, typename = void>
struct CanInstantiateDropView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateDropView<T, hamon::void_t<hamon::ranges::drop_view<T>>>
	: hamon::true_type {};

static_assert(!CanInstantiateDropView<int>::value, "");
static_assert(!CanInstantiateDropView<test_input_range<int>>::value, "");
static_assert( CanInstantiateDropView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateDropView<test_input_view<int> const>::value, "");

template <typename T>
struct ConstNotView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   noexcept { return nullptr; }
};

template <typename T, typename Iterator, typename ConstIterator>
struct NotSimpleSizedView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using sentinel = test_sentinel<iterator>;
	using const_sentinel = test_sentinel<const_iterator>;

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleSizedView(T (&arr)[N]) : NotSimpleSizedView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleSizedView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX11_CONSTEXPR hamon::size_t size() const noexcept
	{
		return static_cast<hamon::size_t>(m_last - m_first);
	}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

template <typename T> using NotSimpleContiguousSizedView    = NotSimpleSizedView<T, contiguous_iterator_wrapper<T>,    contiguous_iterator_wrapper<T const>>;
template <typename T> using NotSimpleRandomAccessSizedView  = NotSimpleSizedView<T, random_access_iterator_wrapper<T>, random_access_iterator_wrapper<T const>>;
template <typename T> using NotSimpleBidirectionalSizedView = NotSimpleSizedView<T, bidirectional_iterator_wrapper<T>, bidirectional_iterator_wrapper<T const>>;
template <typename T> using NotSimpleForwardSizedView       = NotSimpleSizedView<T, forward_iterator_wrapper<T>,       forward_iterator_wrapper<T const>>;
template <typename T> using NotSimpleInputSizedView         = NotSimpleSizedView<T, input_iterator_wrapper<T>,         input_iterator_wrapper<T const>>;
template <typename T> using NotSimpleOutputSizedView        = NotSimpleSizedView<T, output_iterator_wrapper<T>,        output_iterator_wrapper<T const>>;

template <typename T>
struct MoveOnlyView : hamon::ranges::view_base
{
	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};
static_assert(hamon::ranges::view<MoveOnlyView<int>>, "");
static_assert(!hamon::copyable<MoveOnlyView<int>>, "");

template <typename Iterator>
struct SentinelWrapper
{
	Iterator m_it;

	HAMON_CONSTEXPR bool
	operator==(Iterator const& i) const noexcept
	{
		return base(m_it) == base(i);
	}

	HAMON_CONSTEXPR bool
	operator!=(Iterator const& i) const noexcept
	{
		return !(*this == i);
	}
};

template <typename Iterator>
HAMON_CONSTEXPR bool
operator==(Iterator const& i, SentinelWrapper<Iterator> const& s) noexcept
{
	return s == i;
}

template <typename Iterator>
HAMON_CONSTEXPR bool
operator!=(Iterator const& i, SentinelWrapper<Iterator> const& s) noexcept
{
	return !(i == s);
}

template <typename T>
struct SizedViewWithUnsizedSentinel : hamon::ranges::view_base
{
	using iterator = random_access_iterator_wrapper<T>;
	using sentinel = SentinelWrapper<iterator>;

	T* m_first;
	T* m_last;

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR SizedViewWithUnsizedSentinel(T (&arr)[N]) : SizedViewWithUnsizedSentinel(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR SizedViewWithUnsizedSentinel(T* first, T* last) : m_first(first), m_last(last) {}

	constexpr iterator begin() const { return iterator{m_first}; }
	constexpr sentinel end() const { return sentinel{iterator{m_last}}; }
	constexpr std::size_t size() const { return static_cast<std::size_t>(m_last - m_first); }
};
static_assert( hamon::ranges::random_access_range<SizedViewWithUnsizedSentinel<int>>, "");
static_assert( hamon::ranges::sized_range<SizedViewWithUnsizedSentinel<int>>, "");
static_assert(!hamon::sized_sentinel_for<SizedViewWithUnsizedSentinel<int>::sentinel, SizedViewWithUnsizedSentinel<int>::iterator>, "");
static_assert( hamon::ranges::view<SizedViewWithUnsizedSentinel<int>>, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using DV = hamon::ranges::drop_view<V>;

	static_assert(hamon::ranges::range<DV> == true, "");
	static_assert(hamon::ranges::borrowed_range<DV> == hamon::ranges::borrowed_range<V>, "");
	static_assert(hamon::ranges::sized_range<DV> == hamon::ranges::sized_range<V>, "");
	static_assert(hamon::ranges::approximately_sized_range<DV> == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(hamon::ranges::output_range<DV, T> == hamon::ranges::output_range<V, T>, "");
	static_assert(hamon::ranges::input_range<DV> == hamon::ranges::input_range<V>, "");
	static_assert(hamon::ranges::forward_range<DV> == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::ranges::bidirectional_range<DV> == hamon::ranges::bidirectional_range<V>, "");
	static_assert(hamon::ranges::random_access_range<DV> == hamon::ranges::random_access_range<V>, "");
	static_assert(hamon::ranges::contiguous_range<DV> == hamon::ranges::contiguous_range<V>, "");
	static_assert(hamon::ranges::common_range<DV> == hamon::ranges::common_range<V>, "");
	static_assert(hamon::ranges::viewable_range_t<DV>::value == true, "");
	static_assert(hamon::ranges::view<DV> == true, "");
	static_assert(hamon::ranges::constant_range<DV> == false, "");
	
	static_assert(hamon::is_default_constructible<DV>::value == hamon::is_default_constructible<V>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<DV>::value == hamon::is_nothrow_default_constructible<V>::value, "");

	static_assert(!hamon::is_constructible<DV, V>::value, "");
	static_assert( hamon::is_constructible<DV, V, hamon::ptrdiff_t>::value, "");
	static_assert(!hamon::is_constructible<DV, V, int*>::value, "");
	static_assert(!hamon::is_constructible<DV, V, hamon::ptrdiff_t, int>::value, "");

	static_assert(has_base<DV&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<DV&&>::value, "");
	static_assert(has_base<DV const&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<DV const&&>::value == hamon::copy_constructible<V>, "");

	static_assert(has_begin<DV>::value, "");
	static_assert(has_begin<DV const>::value ==
		(hamon::ranges::random_access_range<V const> && hamon::ranges::sized_range<V const>), "");

	static_assert(hamon::same_as<
		decltype(hamon::declval<DV>().begin()),
		decltype(hamon::ranges::begin(hamon::declval<V&>()))>, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_begin<DV const>::value)
	{
		static_assert(hamon::same_as<
			decltype(hamon::declval<DV const>().begin()),
			decltype(hamon::ranges::begin(hamon::declval<V const&>()))>, "");
	}
#endif

	static_assert(has_end<DV>::value, "");
	static_assert(has_end<DV const>::value == hamon::ranges::range<V const>, "");

	static_assert(hamon::same_as<
		decltype(hamon::declval<DV>().end()),
		decltype(hamon::ranges::end(hamon::declval<V&>()))>, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_end<DV const>::value)
	{
		static_assert(hamon::same_as<
			decltype(hamon::declval<DV const>().end()),
			decltype(hamon::ranges::end(hamon::declval<V const&>()))>, "");
	}
#endif

	static_assert(has_size<DV>::value == hamon::ranges::sized_range<V>, "");
	static_assert(has_size<DV const>::value == hamon::ranges::sized_range<V const>, "");

	static_assert(has_reserve_hint<DV&>::value == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(has_reserve_hint<DV const&>::value == hamon::ranges::approximately_sized_range<V const>, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_size<DV>::value)
	{
		static_assert(hamon::same_as<
			decltype(hamon::declval<DV>().size()),
			decltype(hamon::ranges::size(hamon::declval<V&>()))>, "");
	}

	if constexpr (has_size<DV const>::value)
	{
		static_assert(hamon::same_as<
			decltype(hamon::declval<DV const>().size()),
			decltype(hamon::ranges::size(hamon::declval<V const&>()))>, "");
	}
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_random_access_view<int>;
	using DV = hamon::ranges::drop_view<R>;

	static_assert( has_begin<DV&>::value, "");
	static_assert( has_end<DV&>::value, "");
	static_assert( has_empty<DV&>::value, "");
	static_assert( has_cbegin<DV&>::value, "");
	static_assert( has_cend<DV&>::value, "");
	static_assert( has_operator_bool<DV&>::value, "");
	static_assert(!has_data<DV&>::value, "");
	static_assert( has_size<DV&>::value, "");
	static_assert( has_reserve_hint<DV&>::value, "");
	static_assert( has_front<DV&>::value, "");
	static_assert(!has_back<DV&>::value, "");
	static_assert( has_subscript<DV&>::value, "");
	static_assert( has_base<DV&>::value, "");

	static_assert( has_begin<DV const&>::value, "");
	static_assert( has_end<DV const&>::value, "");
	static_assert( has_empty<DV const&>::value, "");
	static_assert( has_cbegin<DV const&>::value, "");
	static_assert( has_cend<DV const&>::value, "");
	static_assert( has_operator_bool<DV const&>::value, "");
	static_assert(!has_data<DV const&>::value, "");
	static_assert( has_size<DV const&>::value, "");
	static_assert( has_reserve_hint<DV const&>::value, "");
	static_assert( has_front<DV const&>::value, "");
	static_assert(!has_back<DV const&>::value, "");
	static_assert( has_subscript<DV const&>::value, "");
	static_assert( has_base<DV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view dv{r, 3};
	static_assert(hamon::same_as<decltype(dv), DV>, "");
#else
	DV dv{r, 3};
#endif
	auto const& cdv = dv;

	VERIFY(dv.size() == 2);
	VERIFY(cdv.size() == 2);
	VERIFY(dv.reserve_hint() == 2);
	VERIFY(cdv.reserve_hint() == 2);

	static_assert( hamon::same_as<decltype(dv.begin()), decltype(r.begin())>, "");
	static_assert(!hamon::same_as<decltype(dv.end()),   decltype(r.begin())>, "");
	static_assert( hamon::same_as<decltype(cdv.begin()), decltype(cr.begin())>, "");
	static_assert(!hamon::same_as<decltype(cdv.end()),   decltype(cr.begin())>, "");

	{
		auto it = dv.begin();
		VERIFY(it == dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it == dv.end());
	}
	{
		auto it = cdv.begin();
		VERIFY(it == cdv.begin());
		VERIFY(it != cdv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != cdv.begin());
		VERIFY(it != cdv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != cdv.begin());
		VERIFY(it == cdv.end());
	}

	VERIFY(dv.base().begin() == r.begin());
	VERIFY(hamon::move(dv).base().begin() == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using R = NotSimpleRandomAccessSizedView<int>;
	using DV = hamon::ranges::drop_view<R>;

	static_assert( has_begin<DV&>::value, "");
	static_assert( has_end<DV&>::value, "");
	static_assert( has_empty<DV&>::value, "");
	static_assert( has_cbegin<DV&>::value, "");
	static_assert( has_cend<DV&>::value, "");
	static_assert( has_operator_bool<DV&>::value, "");
	static_assert(!has_data<DV&>::value, "");
	static_assert( has_size<DV&>::value, "");
	static_assert( has_reserve_hint<DV&>::value, "");
	static_assert( has_front<DV&>::value, "");
	static_assert(!has_back<DV&>::value, "");
	static_assert( has_subscript<DV&>::value, "");
	static_assert( has_base<DV&>::value, "");

	static_assert( has_begin<DV const&>::value, "");
	static_assert( has_end<DV const&>::value, "");
	static_assert( has_empty<DV const&>::value, "");
	static_assert( has_cbegin<DV const&>::value, "");
	static_assert( has_cend<DV const&>::value, "");
	static_assert( has_operator_bool<DV const&>::value, "");
	static_assert(!has_data<DV const&>::value, "");
	static_assert( has_size<DV const&>::value, "");
	static_assert( has_reserve_hint<DV const&>::value, "");
	static_assert( has_front<DV const&>::value, "");
	static_assert(!has_back<DV const&>::value, "");
	static_assert( has_subscript<DV const&>::value, "");
	static_assert( has_base<DV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view dv{r, 2};
	static_assert(hamon::same_as<decltype(dv), DV>, "");
#else
	DV dv{r, 2};
#endif
	auto const& cdv = dv;

	VERIFY(dv.size() == 3);
	VERIFY(cdv.size() == 3);
	VERIFY(dv.reserve_hint() == 3);
	VERIFY(cdv.reserve_hint() == 3);

	static_assert( hamon::same_as<decltype(dv.begin()), decltype(r.begin())>, "");
	static_assert(!hamon::same_as<decltype(dv.end()),   decltype(r.begin())>, "");
	static_assert( hamon::same_as<decltype(cdv.begin()), decltype(cr.begin())>, "");
	static_assert(!hamon::same_as<decltype(cdv.end()),   decltype(cr.begin())>, "");

	{
		auto it = dv.begin();
		VERIFY(it == dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it == dv.end());
	}
	{
		auto it = cdv.begin();
		VERIFY(it == cdv.begin());
		VERIFY(it != cdv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != cdv.begin());
		VERIFY(it != cdv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != cdv.begin());
		VERIFY(it != cdv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != cdv.begin());
		VERIFY(it == cdv.end());
	}

	VERIFY(dv.base().begin() == r.begin());
	VERIFY(hamon::move(dv).base().begin() == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using R = test_forward_view<int>;
	using DV = hamon::ranges::drop_view<R>;

	static_assert( has_begin<DV&>::value, "");
	static_assert( has_end<DV&>::value, "");
	static_assert( has_empty<DV&>::value, "");
	static_assert( has_cbegin<DV&>::value, "");
	static_assert( has_cend<DV&>::value, "");
	static_assert( has_operator_bool<DV&>::value, "");
	static_assert(!has_data<DV&>::value, "");
	static_assert(!has_size<DV&>::value, "");
	static_assert(!has_reserve_hint<DV&>::value, "");
	static_assert( has_front<DV&>::value, "");
	static_assert(!has_back<DV&>::value, "");
	static_assert(!has_subscript<DV&>::value, "");
	static_assert( has_base<DV&>::value, "");

	static_assert(!has_begin<DV const&>::value, "");
	static_assert( has_end<DV const&>::value, "");
	static_assert(!has_empty<DV const&>::value, "");
	static_assert(!has_cbegin<DV const&>::value, "");
	static_assert(!has_cend<DV const&>::value, "");
	static_assert(!has_operator_bool<DV const&>::value, "");
	static_assert(!has_data<DV const&>::value, "");
	static_assert(!has_size<DV const&>::value, "");
	static_assert(!has_reserve_hint<DV const&>::value, "");
	static_assert(!has_front<DV const&>::value, "");
	static_assert(!has_back<DV const&>::value, "");
	static_assert(!has_subscript<DV const&>::value, "");
	static_assert( has_base<DV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view dv{r, 3};
	static_assert(hamon::same_as<decltype(dv), DV>, "");
#else
	DV dv{r, 3};
#endif

	static_assert( hamon::same_as<decltype(dv.begin()), decltype(r.begin())>, "");
	static_assert(!hamon::same_as<decltype(dv.end()),   decltype(r.begin())>, "");

	{
		auto it = dv.begin();
		VERIFY(it == dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it != dv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != dv.begin());
		VERIFY(it == dv.end());
	}

	VERIFY(dv.base().begin() == r.begin());
	VERIFY(hamon::move(dv).base().begin() == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// empty_view
	{
		auto dv = hamon::ranges::empty_view<int>{} | hamon::views::drop(2);
		static_assert(hamon::same_as<decltype(dv), hamon::ranges::empty_view<int>>, "");
		VERIFY(dv.size() == 0);
	}

	// span
	{
		int a[] = {1,2,3,4,5};
		hamon::span<int> s(a);
		auto dv = s | hamon::views::drop(3);
		static_assert( hamon::same_as<decltype(dv), hamon::span<int>>, "");
		VERIFY(dv.size() == 2);
	}
	{
		int a[] = {1,2,3,4,5,6,7,8};
		hamon::span<int, 8> s(a);
		auto dv = s | hamon::views::drop(3);
		static_assert( hamon::same_as<decltype(dv), hamon::span<int, hamon::dynamic_extent>>, "");
		VERIFY(dv.size() == 5);
	}

	// string_view
	{
		hamon::string_view sv = "abcdefg";
		auto dv = sv | hamon::views::drop(4);
		static_assert( hamon::same_as<decltype(dv), hamon::string_view>, "");
		VERIFY(dv.size() == 3);
	}

	// iota_view
	{
		auto dv = hamon::views::iota(1, 8) | hamon::views::drop(3);
		static_assert( hamon::same_as<decltype(dv), hamon::ranges::iota_view<int, int>>, "");
		VERIFY(dv.size() == 4);
		VERIFY(*dv.begin() == 4);
	}
	{
		auto dv = hamon::views::iota(1) | hamon::views::drop(3);
		static_assert( hamon::same_as<decltype(dv),
			hamon::ranges::drop_view<hamon::ranges::iota_view<int, hamon::unreachable_sentinel_t>>>, "");
		static_assert(!has_size<decltype(dv)>::value, "");
		VERIFY(*dv.begin() == 4);
	}

	// subrange
	{
		int a[] = {1,2,3,4,5,6,7,8};
		hamon::ranges::subrange<int*> s(a, a + 5);
		auto dv = s | hamon::views::drop(2);
		static_assert( hamon::same_as<decltype(dv), hamon::ranges::subrange<int*>>, "");
		VERIFY(dv.size() == 3);
	}
	{
		int a[] = {1,2,3,4,5,6,7,8};
		using R = SizedViewWithUnsizedSentinel<int>;
		using I = hamon::ranges::iterator_t<R>;
		using S = hamon::ranges::sentinel_t<R>;
		R r(a);
		hamon::ranges::subrange<I, S, hamon::ranges::subrange_kind::sized> s(r.begin(), r.end(), 8);
		auto dv = s | hamon::views::drop(2);
		static_assert( hamon::same_as<decltype(dv), decltype(s)>, "");
		VERIFY(dv.size() == 6);
	}

	// repeat_view
	{
		auto dv = hamon::views::repeat(42, 8) | hamon::views::drop(3);
		static_assert( hamon::same_as<decltype(dv), hamon::ranges::repeat_view<int, int>>, "");
		VERIFY(dv.size() == 5);
		VERIFY(*dv.begin() == 42);
	}
	{
		auto dv = hamon::views::repeat(42) | hamon::views::drop(3);
		static_assert( hamon::same_as<decltype(dv), decltype(hamon::views::repeat(42))>, "");
		static_assert(!has_size<decltype(dv)>::value, "");
		VERIFY(*dv.begin() == 42);
	}

	{
		int a[] = {1,2,3,4,5};
		auto dv = a | hamon::views::drop(2);
		static_assert(hamon::same_as<decltype(dv), hamon::ranges::drop_view<hamon::ranges::ref_view<int[5]>>>, "");
		VERIFY(dv.size() == 3);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using R = test_input_approximately_sized_view<int>;
	using DV = hamon::ranges::drop_view<R>;

	static_assert( has_begin<DV&>::value, "");
	static_assert( has_end<DV&>::value, "");
	static_assert(!has_empty<DV&>::value, "");
	static_assert( has_cbegin<DV&>::value, "");
	static_assert( has_cend<DV&>::value, "");
	static_assert(!has_operator_bool<DV&>::value, "");
	static_assert(!has_data<DV&>::value, "");
	static_assert(!has_size<DV&>::value, "");
	static_assert( has_reserve_hint<DV&>::value, "");
	static_assert(!has_front<DV&>::value, "");
	static_assert(!has_back<DV&>::value, "");
	static_assert(!has_subscript<DV&>::value, "");
	static_assert( has_base<DV&>::value, "");

	static_assert(!has_begin<DV const&>::value, "");
	static_assert( has_end<DV const&>::value, "");
	static_assert(!has_empty<DV const&>::value, "");
	static_assert(!has_cbegin<DV const&>::value, "");
	static_assert(!has_cend<DV const&>::value, "");
	static_assert(!has_operator_bool<DV const&>::value, "");
	static_assert(!has_data<DV const&>::value, "");
	static_assert(!has_size<DV const&>::value, "");
	static_assert( has_reserve_hint<DV const&>::value, "");
	static_assert(!has_front<DV const&>::value, "");
	static_assert(!has_back<DV const&>::value, "");
	static_assert(!has_subscript<DV const&>::value, "");
	static_assert( has_base<DV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view dv{r, 2};
	static_assert(hamon::same_as<decltype(dv), DV>, "");
#else
	DV dv{r, 2};
#endif
	auto const& cdv = dv;

	VERIFY(dv.reserve_hint() == 3);
	VERIFY(cdv.reserve_hint() == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(ViewsTest, DropViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_output_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_input_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_forward_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_bidirectional_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_random_access_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<test_contiguous_view>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_common_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_borrowed_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_sized_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_approximately_sized_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<ConstNotView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleContiguousSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleRandomAccessSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleBidirectionalSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleForwardSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleInputSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleOutputSizedView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<MoveOnlyView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());

#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
	// [range.drop.overview]/3
	// Example 1:
	{
		std::stringstream ss;
		auto ints = hamon::views::iota(0) | hamon::views::take(10);
		for (auto i : ints | hamon::views::drop(5))
		{
			ss << i << ' ';                             // prints 5 6 7 8 9
		}
		EXPECT_EQ("5 6 7 8 9 ", ss.str());
	}
#endif
}

}	// namespace drop_view_test
}	// namespace hamon_ranges_test
