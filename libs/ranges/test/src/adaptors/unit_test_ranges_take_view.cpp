/**
 *	@file	unit_test_ranges_take_view.cpp
 *
 *	@brief	ranges::take_view のテスト
 */

#include <hamon/ranges/adaptors/take_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/span.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace take_view_test
{

template <typename T, typename = void>
struct CanInstantiateTakeView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateTakeView<T, hamon::void_t<hamon::ranges::take_view<T>>>
	: hamon::true_type {};

static_assert(!CanInstantiateTakeView<int>::value, "");
static_assert(!CanInstantiateTakeView<test_input_range<int>>::value, "");
static_assert( CanInstantiateTakeView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateTakeView<test_input_view<int> const>::value, "");

template <typename T>
struct ConstNotView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   noexcept { return nullptr; }
};

static_assert(!hamon::ranges::detail::simple_view_t<ConstNotView<int>>::value, "");

template <typename T>
struct ConstNotSizedView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   const noexcept { return nullptr; }

	HAMON_CXX14_CONSTEXPR hamon::size_t size() noexcept
	{
		return 0;
	}
};

template <typename T, typename Iterator, typename ConstIterator>
struct NotSimpleView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using sentinel = test_sentinel<iterator>;
	using const_sentinel = test_sentinel<const_iterator>;

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleView(T (&arr)[N]) : NotSimpleView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

template <typename T> using NotSimpleContiguousView    = NotSimpleView<T, contiguous_iterator_wrapper<T>,    contiguous_iterator_wrapper<T const>>;
template <typename T> using NotSimpleRandomAccessView  = NotSimpleView<T, random_access_iterator_wrapper<T>, random_access_iterator_wrapper<T const>>;
template <typename T> using NotSimpleBidirectionalView = NotSimpleView<T, bidirectional_iterator_wrapper<T>, bidirectional_iterator_wrapper<T const>>;
template <typename T> using NotSimpleForwardView       = NotSimpleView<T, forward_iterator_wrapper<T>,       forward_iterator_wrapper<T const>>;
template <typename T> using NotSimpleInputView         = NotSimpleView<T, input_iterator_wrapper<T>,         input_iterator_wrapper<T const>>;
template <typename T> using NotSimpleOutputView        = NotSimpleView<T, output_iterator_wrapper<T>,        output_iterator_wrapper<T const>>;

static_assert(hamon::ranges::view_t<NotSimpleContiguousView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleRandomAccessView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleBidirectionalView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleForwardView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleInputView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleOutputView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleContiguousView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleRandomAccessView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleBidirectionalView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleForwardView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleInputView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleOutputView<int>>::value, "");

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

static_assert(hamon::ranges::view_t<NotSimpleContiguousSizedView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleRandomAccessSizedView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleBidirectionalSizedView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleForwardSizedView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleInputSizedView<int>>::value, "");
static_assert(hamon::ranges::view_t<NotSimpleOutputSizedView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleContiguousSizedView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleRandomAccessSizedView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleBidirectionalSizedView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleForwardSizedView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleInputSizedView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleOutputSizedView<int>>::value, "");
static_assert(hamon::ranges::sized_range_t<NotSimpleContiguousSizedView<int>>::value, "");
static_assert(hamon::ranges::sized_range_t<NotSimpleRandomAccessSizedView<int>>::value, "");
static_assert(hamon::ranges::sized_range_t<NotSimpleBidirectionalSizedView<int>>::value, "");
static_assert(hamon::ranges::sized_range_t<NotSimpleForwardSizedView<int>>::value, "");
static_assert(hamon::ranges::sized_range_t<NotSimpleInputSizedView<int>>::value, "");
static_assert(hamon::ranges::sized_range_t<NotSimpleOutputSizedView<int>>::value, "");

template <typename T>
struct CountedView : hamon::ranges::view_base
{
	using BaseIterator = input_iterator_wrapper<int>;
	using BaseConstIterator = input_iterator_wrapper<int const>;
	using Difference = hamon::iter_difference_t<BaseIterator>;
	
	T* m_first;
	Difference m_count;

	using iterator = hamon::counted_iterator<BaseIterator>;
	using const_iterator = hamon::counted_iterator<BaseConstIterator>;
	using sentinel = hamon::default_sentinel_t;
	using const_sentinel = hamon::default_sentinel_t;

	template <Difference N>
	explicit HAMON_CXX11_CONSTEXPR CountedView(T (&arr)[N]) : CountedView(arr, N) {}

	HAMON_CXX11_CONSTEXPR CountedView(T* first, Difference count) : m_first(first), m_count(count) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{BaseIterator{m_first}, m_count}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{BaseConstIterator{m_first}, m_count}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return hamon::default_sentinel_t{}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return hamon::default_sentinel_t{}; }
};

static_assert(hamon::ranges::view_t<CountedView<int>>::value, "");
static_assert(!hamon::ranges::sized_range_t<CountedView<int>>::value, "");
static_assert(hamon::sized_sentinel_for<hamon::ranges::sentinel_t<CountedView<int>>, hamon::ranges::iterator_t<CountedView<int>>>, "");
static_assert(!hamon::ranges::detail::simple_view_t<CountedView<int>>::value, "");

template <typename T>
struct UnreachableView : hamon::ranges::view_base
{
	T* m_first;

	using iterator = T*;
	using const_iterator = T const*;
	using sentinel = hamon::unreachable_sentinel_t;
	using const_sentinel = hamon::unreachable_sentinel_t;

	explicit HAMON_CXX11_CONSTEXPR UnreachableView(T* first) : m_first(first) {}
	UnreachableView(UnreachableView&&) = default;
	UnreachableView& operator=(UnreachableView&&) = default;

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return hamon::unreachable_sentinel_t{}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return hamon::unreachable_sentinel_t{}; }
};

static_assert(hamon::ranges::view_t<UnreachableView<int>>::value, "");
static_assert(!hamon::ranges::sized_range_t<UnreachableView<int>>::value, "");
static_assert(hamon::ranges::contiguous_range_t<UnreachableView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<UnreachableView<int>>::value, "");
static_assert(!hamon::copyable<UnreachableView<int>>, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using TV = hamon::ranges::take_view<V>;

	static_assert(hamon::default_initializable<TV> == hamon::default_initializable<V>, "");

	static_assert(hamon::ranges::range_t<TV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<TV>::value == hamon::ranges::borrowed_range_t<V>::value, "");
	static_assert(hamon::ranges::sized_range_t<TV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(hamon::ranges::approximately_sized_range<TV> == true, "");
	static_assert(hamon::ranges::output_range_t<TV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<TV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<TV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range<TV> == hamon::ranges::bidirectional_range<V>, "");
	static_assert(hamon::ranges::random_access_range_t<TV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<TV>::value == hamon::ranges::contiguous_range_t<V>::value, "");
	static_assert(hamon::ranges::common_range_t<TV>::value ==
		(hamon::ranges::sized_range_t<V>::value && hamon::ranges::random_access_range_t<V>::value), "");
	static_assert(hamon::ranges::viewable_range_t<TV>::value == true, "");
	static_assert(hamon::ranges::view_t<TV>::value == true, "");
	static_assert(hamon::ranges::constant_range_t<TV>::value == false, "");

	static_assert(hamon::is_default_constructible<TV>::value == hamon::is_default_constructible<V>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<TV>::value == hamon::is_nothrow_default_constructible<V>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<TV>::value == hamon::is_implicitly_default_constructible<V>::value, "");

	static_assert(hamon::is_constructible<TV, V, hamon::ptrdiff_t>::value, "");
#if 0
	static_assert(hamon::is_nothrow_constructible<TV, V, hamon::ptrdiff_t>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<TV, V, hamon::ptrdiff_t>::value, "");

	static_assert(has_base<TV&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<TV&&>::value, "");
	static_assert(has_base<TV const&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<TV const&&>::value == hamon::copy_constructible<V>, "");

	static_assert(has_begin<TV>::value, "");
	static_assert(has_begin<TV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(has_end<TV>::value, "");
	static_assert(has_end<TV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(has_size<TV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(has_size<TV const>::value == hamon::ranges::sized_range_t<V const>::value, "");

	static_assert(has_reserve_hint<TV>::value, "");
	static_assert(has_reserve_hint<TV const>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_random_access_view<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert( has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert( has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	{
		TV t{};
		VERIFY(t.size() == 0);
	}

	int a[] = {1, 2, 3, 4, 5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 3};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 3};
#endif

	auto const& ctv = tv;

	VERIFY(tv.size() == 3);
	VERIFY(ctv.size() == 3);
	VERIFY(tv.reserve_hint() == 3);
	VERIFY(ctv.reserve_hint() == 3);
	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	static_assert(hamon::same_as<decltype(tv.begin()), decltype(r.begin())>, "");
	static_assert(hamon::same_as<decltype(tv.end()),   decltype(r.begin())>, "");
	static_assert(hamon::same_as<decltype(ctv.begin()), decltype(r.begin())>, "");
	static_assert(hamon::same_as<decltype(ctv.end()),   decltype(r.begin())>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using R = test_random_access_view<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert( has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert( has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 10};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 10};
#endif
	auto const& ctv = tv;

	VERIFY(tv.size() == 5);
	VERIFY(ctv.size() == 5);
	VERIFY(tv.reserve_hint() == 5);
	VERIFY(ctv.reserve_hint() == 5);
	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	static_assert(hamon::same_as<decltype(tv.begin()), decltype(r.begin())>, "");
	static_assert(hamon::same_as<decltype(tv.end()),   decltype(r.begin())>, "");
	static_assert(hamon::same_as<decltype(ctv.begin()), decltype(r.begin())>, "");
	static_assert(hamon::same_as<decltype(ctv.end()),   decltype(r.begin())>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using R = NotSimpleRandomAccessView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert( has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert( has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 2};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 2};
#endif
	auto const& ctv = tv;

	VERIFY(tv.size() == 2);
	VERIFY(ctv.size() == 2);
	VERIFY(tv.reserve_hint() == 2);
	VERIFY(ctv.reserve_hint() == 2);
	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	static_assert( hamon::same_as<decltype(tv.begin()), decltype(r.begin())>, "");
	static_assert( hamon::same_as<decltype(tv.end()),   decltype(r.begin())>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), decltype(cr.begin())>, "");
	static_assert( hamon::same_as<decltype(ctv.end()),   decltype(cr.begin())>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using R = NotSimpleForwardView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert(!has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert(!has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 4};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 4};
#endif
	auto const& ctv = tv;

	VERIFY(tv.reserve_hint() == 4);
	VERIFY(ctv.reserve_hint() == 4);

	static_assert(!has_size<decltype(tv)>::value, "");
	static_assert(!has_size<decltype(ctv)>::value, "");
	static_assert( has_reserve_hint<decltype(tv)>::value, "");
	static_assert( has_reserve_hint<decltype(ctv)>::value, "");

	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	static_assert( hamon::same_as<decltype(tv.begin()), hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert(!hamon::same_as<decltype(tv.end()),   hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert(!hamon::same_as<decltype(tv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(tv.end().base()), decltype(r.end())>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert(!hamon::same_as<decltype(ctv.end()),   hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert(!hamon::same_as<decltype(ctv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(ctv.end().base()), decltype(cr.end())>, "");

	{
		using Iter  = decltype(tv.begin());
		using CIter = decltype(ctv.begin());
		using Sent  = decltype(tv.end());
		using CSent = decltype(ctv.end());

		static_assert( has_eq  <Iter, Iter>::value, "");
		static_assert(!has_eq  <Iter, CIter>::value, "");
		static_assert( has_eq  <Iter, Sent>::value, "");
		static_assert(!has_eq  <Iter, CSent>::value, "");
		static_assert( has_neq <Iter, Iter>::value, "");
		static_assert(!has_neq <Iter, CIter>::value, "");
		static_assert( has_neq <Iter, Sent>::value, "");
		static_assert(!has_neq <Iter, CSent>::value, "");
		static_assert( has_lt  <Iter, Iter>::value, "");
		static_assert(!has_lt  <Iter, CIter>::value, "");
		static_assert(!has_lt  <Iter, Sent>::value, "");
		static_assert(!has_lt  <Iter, CSent>::value, "");
		static_assert( has_lteq<Iter, Iter>::value, "");
		static_assert(!has_lteq<Iter, CIter>::value, "");
		static_assert(!has_lteq<Iter, Sent>::value, "");
		static_assert(!has_lteq<Iter, CSent>::value, "");
		static_assert( has_gt  <Iter, Iter>::value, "");
		static_assert(!has_gt  <Iter, CIter>::value, "");
		static_assert(!has_gt  <Iter, Sent>::value, "");
		static_assert(!has_gt  <Iter, CSent>::value, "");
		static_assert( has_gteq<Iter, Iter>::value, "");
		static_assert(!has_gteq<Iter, CIter>::value, "");
		static_assert(!has_gteq<Iter, Sent>::value, "");
		static_assert(!has_gteq<Iter, CSent>::value, "");

		static_assert(!has_eq  <CIter, Iter>::value, "");
		static_assert( has_eq  <CIter, CIter>::value, "");
		static_assert(!has_eq  <CIter, Sent>::value, "");
		static_assert( has_eq  <CIter, CSent>::value, "");
		static_assert(!has_neq <CIter, Iter>::value, "");
		static_assert( has_neq <CIter, CIter>::value, "");
		static_assert(!has_neq <CIter, Sent>::value, "");
		static_assert( has_neq <CIter, CSent>::value, "");
		static_assert(!has_lt  <CIter, Iter>::value, "");
		static_assert( has_lt  <CIter, CIter>::value, "");
		static_assert(!has_lt  <CIter, Sent>::value, "");
		static_assert(!has_lt  <CIter, CSent>::value, "");
		static_assert(!has_lteq<CIter, Iter>::value, "");
		static_assert( has_lteq<CIter, CIter>::value, "");
		static_assert(!has_lteq<CIter, Sent>::value, "");
		static_assert(!has_lteq<CIter, CSent>::value, "");
		static_assert(!has_gt  <CIter, Iter>::value, "");
		static_assert( has_gt  <CIter, CIter>::value, "");
		static_assert(!has_gt  <CIter, Sent>::value, "");
		static_assert(!has_gt  <CIter, CSent>::value, "");
		static_assert(!has_gteq<CIter, Iter>::value, "");
		static_assert( has_gteq<CIter, CIter>::value, "");
		static_assert(!has_gteq<CIter, Sent>::value, "");
		static_assert(!has_gteq<CIter, CSent>::value, "");

		static_assert( has_eq  <Sent, Iter>::value, "");
		static_assert(!has_eq  <Sent, CIter>::value, "");
		static_assert(!has_eq  <Sent, Sent>::value, "");
		static_assert(!has_eq  <Sent, CSent>::value, "");
		static_assert( has_neq <Sent, Iter>::value, "");
		static_assert(!has_neq <Sent, CIter>::value, "");
		static_assert(!has_neq <Sent, Sent>::value, "");
		static_assert(!has_neq <Sent, CSent>::value, "");
		static_assert(!has_lt  <Sent, Iter>::value, "");
		static_assert(!has_lt  <Sent, CIter>::value, "");
		static_assert(!has_lt  <Sent, Sent>::value, "");
		static_assert(!has_lt  <Sent, CSent>::value, "");
		static_assert(!has_lteq<Sent, Iter>::value, "");
		static_assert(!has_lteq<Sent, CIter>::value, "");
		static_assert(!has_lteq<Sent, Sent>::value, "");
		static_assert(!has_lteq<Sent, CSent>::value, "");
		static_assert(!has_gt  <Sent, Iter>::value, "");
		static_assert(!has_gt  <Sent, CIter>::value, "");
		static_assert(!has_gt  <Sent, Sent>::value, "");
		static_assert(!has_gt  <Sent, CSent>::value, "");
		static_assert(!has_gteq<Sent, Iter>::value, "");
		static_assert(!has_gteq<Sent, CIter>::value, "");
		static_assert(!has_gteq<Sent, Sent>::value, "");
		static_assert(!has_gteq<Sent, CSent>::value, "");

		static_assert(!has_eq  <CSent, Iter>::value, "");
		static_assert( has_eq  <CSent, CIter>::value, "");
		static_assert(!has_eq  <CSent, Sent>::value, "");
		static_assert(!has_eq  <CSent, CSent>::value, "");
		static_assert(!has_neq <CSent, Iter>::value, "");
		static_assert( has_neq <CSent, CIter>::value, "");
		static_assert(!has_neq <CSent, Sent>::value, "");
		static_assert(!has_neq <CSent, CSent>::value, "");
		static_assert(!has_lt  <CSent, Iter>::value, "");
		static_assert(!has_lt  <CSent, CIter>::value, "");
		static_assert(!has_lt  <CSent, Sent>::value, "");
		static_assert(!has_lt  <CSent, CSent>::value, "");
		static_assert(!has_lteq<CSent, Iter>::value, "");
		static_assert(!has_lteq<CSent, CIter>::value, "");
		static_assert(!has_lteq<CSent, Sent>::value, "");
		static_assert(!has_lteq<CSent, CSent>::value, "");
		static_assert(!has_gt  <CSent, Iter>::value, "");
		static_assert(!has_gt  <CSent, CIter>::value, "");
		static_assert(!has_gt  <CSent, Sent>::value, "");
		static_assert(!has_gt  <CSent, CSent>::value, "");
		static_assert(!has_gteq<CSent, Iter>::value, "");
		static_assert(!has_gteq<CSent, CIter>::value, "");
		static_assert(!has_gteq<CSent, Sent>::value, "");
		static_assert(!has_gteq<CSent, CSent>::value, "");
	}

	using Sentinel = decltype(tv.end());
	using ConstSentinel = decltype(ctv.end());
	static_assert(!hamon::same_as<Sentinel, ConstSentinel>, "");
	static_assert(!hamon::constructible_from<Sentinel, ConstSentinel>, "");
	static_assert(!hamon::constructible_from<ConstSentinel, Sentinel>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == tv.end());
		VERIFY(tv.end().base().m_it.m_ptr == a + 9);
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == ctv.end());
		VERIFY(ctv.end().base().m_it.m_ptr == a + 9);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using R = NotSimpleForwardSizedView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 4};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 4};
#endif
	auto const& ctv = tv;

	VERIFY(tv.size() == 4);
	VERIFY(ctv.size() == 4);
	VERIFY(tv.reserve_hint() == 4);
	VERIFY(ctv.reserve_hint() == 4);
	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	static_assert( hamon::same_as<decltype(tv.begin()), hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert( hamon::same_as<decltype(tv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert( hamon::same_as<decltype(ctv.end()),   hamon::default_sentinel_t>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	using R = NotSimpleForwardSizedView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert( has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert( has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 999};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 999};
#endif
	auto const& ctv = tv;

	VERIFY(tv.size() == 6);
	VERIFY(ctv.size() == 6);
	VERIFY(tv.reserve_hint() == 6);
	VERIFY(ctv.reserve_hint() == 6);
	VERIFY(tv.base().begin() == r.begin());
	VERIFY(hamon::move(tv).base().begin() == r.begin());

	static_assert( hamon::same_as<decltype(tv.begin()), hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert( hamon::same_as<decltype(tv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert( hamon::same_as<decltype(ctv.end()),   hamon::default_sentinel_t>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test07()
{
	using R = CountedView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert(!has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert(!has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert(!has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert(!has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert(!has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert(!has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert(!has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert(!has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 3};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 3};
#endif
	auto const& ctv = tv;

	VERIFY(tv.reserve_hint() == 3);
	VERIFY(ctv.reserve_hint() == 3);

	static_assert(!has_size<decltype(tv)>::value, "");
	static_assert(!has_size<decltype(ctv)>::value, "");
	static_assert( has_reserve_hint<decltype(tv)>::value, "");
	static_assert( has_reserve_hint<decltype(ctv)>::value, "");

	static_assert( hamon::same_as<decltype(tv.begin()), hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert( hamon::same_as<decltype(tv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert( hamon::same_as<decltype(ctv.end()),   hamon::default_sentinel_t>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test08()
{
	using R = CountedView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert(!has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert(!has_operator_bool<TV&>::value, "");
	static_assert(!has_data<TV&>::value, "");
	static_assert(!has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert(!has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert(!has_subscript<TV&>::value, "");
	static_assert( has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert(!has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert(!has_operator_bool<TV const&>::value, "");
	static_assert(!has_data<TV const&>::value, "");
	static_assert(!has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert(!has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert(!has_subscript<TV const&>::value, "");
	static_assert( has_base<TV const&>::value, "");

	int a[] = {1, 2, 3};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{r, 10};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{r, 10};
#endif
	auto const& ctv = tv;

	VERIFY(tv.reserve_hint() == 10);
	VERIFY(ctv.reserve_hint() == 10);

	static_assert(!has_size<decltype(tv)>::value, "");
	static_assert(!has_size<decltype(ctv)>::value, "");
	static_assert( has_reserve_hint<decltype(tv)>::value, "");
	static_assert( has_reserve_hint<decltype(ctv)>::value, "");

	static_assert( hamon::same_as<decltype(tv.begin()), hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert( hamon::same_as<decltype(tv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert( hamon::same_as<decltype(ctv.end()),   hamon::default_sentinel_t>, "");

	{
		auto it = tv.begin();
		VERIFY(it != tv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != tv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == tv.end());
	}
	{
		auto it = ctv.begin();
		VERIFY(it != ctv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != ctv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == ctv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test09()
{
	using R = UnreachableView<int>;
	using TV = hamon::ranges::take_view<R>;

	static_assert( has_begin<TV&>::value, "");
	static_assert( has_end<TV&>::value, "");
	static_assert( has_empty<TV&>::value, "");
	static_assert( has_cbegin<TV&>::value, "");
	static_assert( has_cend<TV&>::value, "");
	static_assert( has_operator_bool<TV&>::value, "");
	static_assert( has_data<TV&>::value, "");
	static_assert(!has_size<TV&>::value, "");
	static_assert( has_reserve_hint<TV&>::value, "");
	static_assert( has_front<TV&>::value, "");
	static_assert(!has_back<TV&>::value, "");
	static_assert( has_subscript<TV&>::value, "");
	static_assert(!has_base<TV&>::value, "");

	static_assert( has_begin<TV const&>::value, "");
	static_assert( has_end<TV const&>::value, "");
	static_assert( has_empty<TV const&>::value, "");
	static_assert( has_cbegin<TV const&>::value, "");
	static_assert( has_cend<TV const&>::value, "");
	static_assert( has_operator_bool<TV const&>::value, "");
	static_assert( has_data<TV const&>::value, "");
	static_assert(!has_size<TV const&>::value, "");
	static_assert( has_reserve_hint<TV const&>::value, "");
	static_assert( has_front<TV const&>::value, "");
	static_assert(!has_back<TV const&>::value, "");
	static_assert( has_subscript<TV const&>::value, "");
	static_assert(!has_base<TV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view tv{hamon::move(r), 3};
	static_assert(hamon::same_as<decltype(tv), TV>, "");
#else
	TV tv{hamon::move(r), 3};
#endif
	auto const& ctv = tv;

	static_assert( hamon::same_as<decltype(tv.begin()), hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert(!hamon::same_as<decltype(tv.end()),   hamon::counted_iterator<decltype(r.begin())>>, "");
	static_assert(!hamon::same_as<decltype(tv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(tv.end().base()), decltype(r.end())>, "");
	static_assert( hamon::same_as<decltype(ctv.begin()), hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert(!hamon::same_as<decltype(ctv.end()),   hamon::counted_iterator<decltype(cr.begin())>>, "");
	static_assert(!hamon::same_as<decltype(ctv.end()),   hamon::default_sentinel_t>, "");
	static_assert( hamon::same_as<decltype(ctv.end().base()), decltype(cr.end())>, "");

	{
		using Iter  = decltype(tv.begin());
		using CIter = decltype(ctv.begin());
		using Sent  = decltype(tv.end());
		using CSent = decltype(ctv.end());

		static_assert( has_eq  <Iter, Iter>::value, "");
		static_assert( has_eq  <Iter, CIter>::value, "");
		static_assert( has_eq  <Iter, Sent>::value, "");
		static_assert( has_eq  <Iter, CSent>::value, "");
		static_assert( has_neq <Iter, Iter>::value, "");
		static_assert( has_neq <Iter, CIter>::value, "");
		static_assert( has_neq <Iter, Sent>::value, "");
		static_assert( has_neq <Iter, CSent>::value, "");
		static_assert( has_lt  <Iter, Iter>::value, "");
		static_assert( has_lt  <Iter, CIter>::value, "");
		static_assert(!has_lt  <Iter, Sent>::value, "");
		static_assert(!has_lt  <Iter, CSent>::value, "");
		static_assert( has_lteq<Iter, Iter>::value, "");
		static_assert( has_lteq<Iter, CIter>::value, "");
		static_assert(!has_lteq<Iter, Sent>::value, "");
		static_assert(!has_lteq<Iter, CSent>::value, "");
		static_assert( has_gt  <Iter, Iter>::value, "");
		static_assert( has_gt  <Iter, CIter>::value, "");
		static_assert(!has_gt  <Iter, Sent>::value, "");
		static_assert(!has_gt  <Iter, CSent>::value, "");
		static_assert( has_gteq<Iter, Iter>::value, "");
		static_assert( has_gteq<Iter, CIter>::value, "");
		static_assert(!has_gteq<Iter, Sent>::value, "");
		static_assert(!has_gteq<Iter, CSent>::value, "");

		static_assert( has_eq  <CIter, Iter>::value, "");
		static_assert( has_eq  <CIter, CIter>::value, "");
		static_assert( has_eq  <CIter, Sent>::value, "");
		static_assert( has_eq  <CIter, CSent>::value, "");
		static_assert( has_neq <CIter, Iter>::value, "");
		static_assert( has_neq <CIter, CIter>::value, "");
		static_assert( has_neq <CIter, Sent>::value, "");
		static_assert( has_neq <CIter, CSent>::value, "");
		static_assert( has_lt  <CIter, Iter>::value, "");
		static_assert( has_lt  <CIter, CIter>::value, "");
		static_assert(!has_lt  <CIter, Sent>::value, "");
		static_assert(!has_lt  <CIter, CSent>::value, "");
		static_assert( has_lteq<CIter, Iter>::value, "");
		static_assert( has_lteq<CIter, CIter>::value, "");
		static_assert(!has_lteq<CIter, Sent>::value, "");
		static_assert(!has_lteq<CIter, CSent>::value, "");
		static_assert( has_gt  <CIter, Iter>::value, "");
		static_assert( has_gt  <CIter, CIter>::value, "");
		static_assert(!has_gt  <CIter, Sent>::value, "");
		static_assert(!has_gt  <CIter, CSent>::value, "");
		static_assert( has_gteq<CIter, Iter>::value, "");
		static_assert( has_gteq<CIter, CIter>::value, "");
		static_assert(!has_gteq<CIter, Sent>::value, "");
		static_assert(!has_gteq<CIter, CSent>::value, "");

		static_assert( has_eq  <Sent, Iter>::value, "");
		static_assert( has_eq  <Sent, CIter>::value, "");
		static_assert(!has_eq  <Sent, Sent>::value, "");
		static_assert(!has_eq  <Sent, CSent>::value, "");
		static_assert( has_neq <Sent, Iter>::value, "");
		static_assert( has_neq <Sent, CIter>::value, "");
		static_assert(!has_neq <Sent, Sent>::value, "");
		static_assert(!has_neq <Sent, CSent>::value, "");
		static_assert(!has_lt  <Sent, Iter>::value, "");
		static_assert(!has_lt  <Sent, CIter>::value, "");
		static_assert(!has_lt  <Sent, Sent>::value, "");
		static_assert(!has_lt  <Sent, CSent>::value, "");
		static_assert(!has_lteq<Sent, Iter>::value, "");
		static_assert(!has_lteq<Sent, CIter>::value, "");
		static_assert(!has_lteq<Sent, Sent>::value, "");
		static_assert(!has_lteq<Sent, CSent>::value, "");
		static_assert(!has_gt  <Sent, Iter>::value, "");
		static_assert(!has_gt  <Sent, CIter>::value, "");
		static_assert(!has_gt  <Sent, Sent>::value, "");
		static_assert(!has_gt  <Sent, CSent>::value, "");
		static_assert(!has_gteq<Sent, Iter>::value, "");
		static_assert(!has_gteq<Sent, CIter>::value, "");
		static_assert(!has_gteq<Sent, Sent>::value, "");
		static_assert(!has_gteq<Sent, CSent>::value, "");

		static_assert( has_eq  <CSent, Iter>::value, "");
		static_assert( has_eq  <CSent, CIter>::value, "");
		static_assert(!has_eq  <CSent, Sent>::value, "");
		static_assert(!has_eq  <CSent, CSent>::value, "");
		static_assert( has_neq <CSent, Iter>::value, "");
		static_assert( has_neq <CSent, CIter>::value, "");
		static_assert(!has_neq <CSent, Sent>::value, "");
		static_assert(!has_neq <CSent, CSent>::value, "");
		static_assert(!has_lt  <CSent, Iter>::value, "");
		static_assert(!has_lt  <CSent, CIter>::value, "");
		static_assert(!has_lt  <CSent, Sent>::value, "");
		static_assert(!has_lt  <CSent, CSent>::value, "");
		static_assert(!has_lteq<CSent, Iter>::value, "");
		static_assert(!has_lteq<CSent, CIter>::value, "");
		static_assert(!has_lteq<CSent, Sent>::value, "");
		static_assert(!has_lteq<CSent, CSent>::value, "");
		static_assert(!has_gt  <CSent, Iter>::value, "");
		static_assert(!has_gt  <CSent, CIter>::value, "");
		static_assert(!has_gt  <CSent, Sent>::value, "");
		static_assert(!has_gt  <CSent, CSent>::value, "");
		static_assert(!has_gteq<CSent, Iter>::value, "");
		static_assert(!has_gteq<CSent, CIter>::value, "");
		static_assert(!has_gteq<CSent, Sent>::value, "");
		static_assert(!has_gteq<CSent, CSent>::value, "");
	}

	using Sentinel = decltype(tv.end());
	using ConstSentinel = decltype(ctv.end());
	static_assert(!hamon::same_as<Sentinel, ConstSentinel>, "");
	static_assert(!hamon::constructible_from<Sentinel, ConstSentinel>, "");
	static_assert( hamon::constructible_from<ConstSentinel, Sentinel>, "");

	{
		Sentinel s{};
		VERIFY(tv.begin() != s);
		VERIFY(ctv.begin() != s);
	}
	{
		ConstSentinel cs{};
		VERIFY(tv.begin() != cs);
		VERIFY(ctv.begin() != cs);
	}

	Sentinel s = tv.end();
	ConstSentinel cs = s;

	auto it = tv.begin();
	VERIFY(it != s);
	VERIFY(it != cs);
	VERIFY(s  != it);
	VERIFY(cs != it);
	++it;
	VERIFY(it != s);
	VERIFY(it != cs);
	VERIFY(s  != it);
	VERIFY(cs != it);
	++it;
	VERIFY(it != s);
	VERIFY(it != cs);
	VERIFY(s  != it);
	VERIFY(cs != it);
	++it;
	VERIFY(it == s);
	VERIFY(it == cs);
	VERIFY(s  == it);
	VERIFY(cs == it);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test10()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	{
		using R = test_forward_sized_view<int>;
		R r(a);
		auto tv = r | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<R>>, "");
		VERIFY(tv.base().begin() == r.begin());
		VERIFY(tv.base().end() == r.end());
		VERIFY(tv.size() == 3);
		VERIFY(tv.reserve_hint() == 3);

		auto rv2 = hamon::views::take(r, 3);
		static_assert( hamon::same_as<decltype(tv), decltype(rv2)>, "");
	}
	{
		auto tv = a | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<hamon::ranges::ref_view<int[9]>>>, "");
		VERIFY(tv.base().begin() == a);
		VERIFY(tv.base().end() == a + 9);
		VERIFY(tv.size() == 3);
		VERIFY(tv.reserve_hint() == 3);

		auto rv2 = hamon::views::take(a, 3);
		static_assert( hamon::same_as<decltype(tv), decltype(rv2)>, "");
	}
	{
		auto tv = a | hamon::views::take(5) | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<hamon::ranges::take_view<hamon::ranges::ref_view<int[9]>>>>, "");
		VERIFY(tv.base().base().begin() == a);
		VERIFY(tv.base().base().end() == a + 9);
		VERIFY(tv.size() == 3);
		VERIFY(tv.reserve_hint() == 3);
		VERIFY(*tv.begin() == 1);

		auto rv2 = hamon::views::take(hamon::views::take(a, 5), 3);
		static_assert( hamon::same_as<decltype(tv), decltype(rv2)>, "");
	}

	struct Double
	{
		constexpr int operator()(int x) const
		{
			return x * 2;
		}
	};

	{
		auto tv = a | hamon::views::transform(Double{}) | hamon::views::take(4);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<hamon::ranges::transform_view<hamon::ranges::ref_view<int[9]>, Double>>>, "");
		VERIFY(tv.size() == 4);
		VERIFY(tv.reserve_hint() == 4);
		VERIFY(*tv.begin() == 2);
	}
	{
		auto tv = a | hamon::views::take(4) | hamon::views::transform(Double{});
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::transform_view<hamon::ranges::take_view<hamon::ranges::ref_view<int[9]>>, Double>>, "");
		VERIFY(tv.size() == 4);
		VERIFY(tv.reserve_hint() == 4);
		VERIFY(*tv.begin() == 2);
	}
	{
		auto partial = hamon::views::transform(Double{}) | hamon::views::take(4);
		auto tv = a | partial;
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<hamon::ranges::transform_view<hamon::ranges::ref_view<int[9]>, Double>>>, "");
		VERIFY(tv.size() == 4);
		VERIFY(tv.reserve_hint() == 4);
		VERIFY(*tv.begin() == 2);
	}

	{
		hamon::ranges::empty_view<int> r;
		auto tv = r | hamon::views::take(5);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::empty_view<int>>, "");
		VERIFY(tv.size() == 0);
	}
	{
		hamon::span<int> s(a);
		auto tv = s | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::span<int>>, "");
		VERIFY(tv.size() == 3);
	}
	{
		hamon::span<int, 9> s(a);
		auto tv = s | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::span<int, hamon::dynamic_extent>>, "");
		VERIFY(tv.size() == 3);
	}
	{
		hamon::string_view sv = "abcdefg";
		auto tv = sv | hamon::views::take(4);
		static_assert( hamon::same_as<decltype(tv), hamon::string_view>, "");
		VERIFY(tv.size() == 4);
	}
	{
		hamon::ranges::subrange<int*> s(a, a + 5);
		auto tv = s | hamon::views::take(4);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::subrange<int*>>, "");
		VERIFY(tv.size() == 4);
	}
	{
		using R = test_forward_sized_view<int>;
		using I = hamon::ranges::iterator_t<R>;
		using S = hamon::ranges::sentinel_t<R>;
		R r(a);
		hamon::ranges::subrange<I, S> s(r.begin(), r.end());
		auto tv = s | hamon::views::take(4);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<decltype(s)>>, "");
		static_assert(has_size<decltype(tv)>::value == false, "");
	}
	{
		auto tv = hamon::views::iota(1, 8) | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::iota_view<int, int>>, "");
		VERIFY(tv.size() == 3);
		VERIFY(*tv.begin() == 1);
	}
	{
		auto tv = hamon::views::iota(1) | hamon::views::take(3);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::take_view<hamon::ranges::iota_view<int, hamon::unreachable_sentinel_t>>>, "");
		static_assert(has_size<decltype(tv)>::value == false, "");
		VERIFY(*tv.begin() == 1);
	}
	{
		auto tv = hamon::views::repeat(42, 8) | hamon::views::take(4);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::repeat_view<int, int>>, "");
		VERIFY(tv.size() == 4);
		VERIFY(*tv.begin() == 42);
	}
	{
		auto tv = hamon::views::repeat(42) | hamon::views::take(4);
		static_assert( hamon::same_as<decltype(tv), hamon::ranges::repeat_view<int, hamon::ranges::range_difference_t<decltype(hamon::views::repeat(42))>>>, "");
		VERIFY(tv.size() == 4);
		VERIFY(*tv.begin() == 42);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, TakeViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());

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
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<ConstNotSizedView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleContiguousView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleRandomAccessView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleBidirectionalView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleForwardView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleInputView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleOutputView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleContiguousSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleRandomAccessSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleBidirectionalSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleForwardSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleInputSizedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleOutputSizedView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<CountedView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<UnreachableView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test08());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test09());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test10());

	// [range.take.overview]/3
	// Example 1:
	{
		std::stringstream ss;
		hamon::vector<int> is {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (int i : is | hamon::views::take(5))
		{
			ss << i << ' '; // prints 0 1 2 3 4
		}
		EXPECT_EQ("0 1 2 3 4 ", ss.str());
	}
}

}	// namespace take_view_test
}	// namespace hamon_ranges_test
