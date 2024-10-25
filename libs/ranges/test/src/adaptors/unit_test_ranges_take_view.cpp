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

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_eq<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_neq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_neq<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_lt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lt<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_lteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lteq<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_gt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gt<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_gteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gteq<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U, typename = void>
struct has_compare_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_compare_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

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
static_assert(hamon::sized_sentinel_for_t<hamon::ranges::sentinel_t<CountedView<int>>, hamon::ranges::iterator_t<CountedView<int>>>::value, "");
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
static_assert(!hamon::copyable_t<UnreachableView<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using RV = hamon::ranges::take_view<V>;

	static_assert(hamon::default_initializable_t<RV>::value == hamon::default_initializable_t<V>::value, "");

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == hamon::ranges::borrowed_range_t<V>::value, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == hamon::ranges::contiguous_range_t<V>::value, "");
	static_assert(hamon::ranges::common_range_t<RV>::value ==
		(hamon::ranges::sized_range_t<V>::value && hamon::ranges::random_access_range_t<V>::value), "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");

	static_assert(hamon::is_default_constructible<RV>::value == hamon::is_default_constructible<V>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value == hamon::is_nothrow_default_constructible<V>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<RV>::value == hamon::is_implicitly_default_constructible<V>::value, "");

	static_assert(hamon::is_constructible<RV, V, hamon::ptrdiff_t>::value, "");
#if 0
	static_assert(hamon::is_nothrow_constructible<RV, V, hamon::ptrdiff_t>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<RV, V, hamon::ptrdiff_t>::value, "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(has_begin<RV>::value, "");
	static_assert(has_begin<RV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(has_end<RV>::value, "");
	static_assert(has_end<RV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(has_size<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(has_size<RV const>::value == hamon::ranges::sized_range_t<V const>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5};
	using R = test_random_access_view<int>;
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 3};
#else
	hamon::ranges::take_view<R> rv{r, 3};
#endif
	using RV = decltype(rv);

	{
		RV t{};
		VERIFY(t.size() == 0);
	}

	auto const& crv = rv;

	VERIFY(rv.size() == 3);
	VERIFY(crv.size() == 3);
	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	static_assert(hamon::same_as_t<decltype(rv.begin()), decltype(r.begin())>::value, "");
	static_assert(hamon::same_as_t<decltype(rv.end()),   decltype(r.begin())>::value, "");
	static_assert(hamon::same_as_t<decltype(crv.begin()), decltype(r.begin())>::value, "");
	static_assert(hamon::same_as_t<decltype(crv.end()),   decltype(r.begin())>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5};
	using R = test_random_access_view<int>;
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 10};
#else
	hamon::ranges::take_view<R> rv{r, 10};
#endif
	auto const& crv = rv;

	VERIFY(rv.size() == 5);
	VERIFY(crv.size() == 5);
	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	static_assert(hamon::same_as_t<decltype(rv.begin()), decltype(r.begin())>::value, "");
	static_assert(hamon::same_as_t<decltype(rv.end()),   decltype(r.begin())>::value, "");
	static_assert(hamon::same_as_t<decltype(crv.begin()), decltype(r.begin())>::value, "");
	static_assert(hamon::same_as_t<decltype(crv.end()),   decltype(r.begin())>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	using R = NotSimpleRandomAccessView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 2};
#else
	hamon::ranges::take_view<R> rv{r, 2};
#endif
	auto const& crv = rv;

	VERIFY(rv.size() == 2);
	VERIFY(crv.size() == 2);
	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	static_assert( hamon::same_as_t<decltype(rv.begin()), decltype(r.begin())>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end()),   decltype(r.begin())>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), decltype(cr.begin())>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end()),   decltype(cr.begin())>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	using R = NotSimpleForwardView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 4};
#else
	hamon::ranges::take_view<R> rv{r, 4};
#endif
	auto const& crv = rv;

	static_assert(!has_size<decltype(rv)>::value, "");
	static_assert(!has_size<decltype(crv)>::value, "");

	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	static_assert( hamon::same_as_t<decltype(rv.begin()), hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end().base()), decltype(r.end())>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(crv.end()),   hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(crv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end().base()), decltype(cr.end())>::value, "");

	{
		using Iter  = decltype(rv.begin());
		using CIter = decltype(crv.begin());
		using Sent  = decltype(rv.end());
		using CSent = decltype(crv.end());

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

	using Sentinel = decltype(rv.end());
	using ConstSentinel = decltype(crv.end());
	static_assert(!hamon::same_as_t<Sentinel, ConstSentinel>::value, "");
	static_assert(!hamon::constructible_from_t<Sentinel, ConstSentinel>::value, "");
	static_assert(!hamon::constructible_from_t<ConstSentinel, Sentinel>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == rv.end());
		VERIFY(rv.end().base().m_it.m_ptr == a + 9);
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == crv.end());
		VERIFY(crv.end().base().m_it.m_ptr == a + 9);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int a[] = {1, 2, 3, 4, 5, 6};
	using R = NotSimpleForwardSizedView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 4};
#else
	hamon::ranges::take_view<R> rv{r, 4};
#endif
	auto const& crv = rv;

	VERIFY(rv.size() == 4);
	VERIFY(crv.size() == 4);
	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	static_assert( hamon::same_as_t<decltype(rv.begin()), hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end()),   hamon::default_sentinel_t>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	int a[] = {1, 2, 3, 4, 5, 6};
	using R = NotSimpleForwardSizedView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 999};
#else
	hamon::ranges::take_view<R> rv{r, 999};
#endif
	auto const& crv = rv;

	VERIFY(rv.size() == 6);
	VERIFY(crv.size() == 6);
	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	static_assert( hamon::same_as_t<decltype(rv.begin()), hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end()),   hamon::default_sentinel_t>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test07()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	using R = CountedView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 3};
#else
	hamon::ranges::take_view<R> rv{r, 3};
#endif
	auto const& crv = rv;

	static_assert(!has_size<decltype(rv)>::value, "");
	static_assert(!has_size<decltype(crv)>::value, "");

	static_assert( hamon::same_as_t<decltype(rv.begin()), hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end()),   hamon::default_sentinel_t>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test08()
{
	int a[] = {1, 2, 3};
	using R = CountedView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{r, 10};
#else
	hamon::ranges::take_view<R> rv{r, 10};
#endif
	auto const& crv = rv;

	static_assert(!has_size<decltype(rv)>::value, "");
	static_assert(!has_size<decltype(crv)>::value, "");

	static_assert( hamon::same_as_t<decltype(rv.begin()), hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end()),   hamon::default_sentinel_t>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it != crv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it == crv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test09()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	using R = UnreachableView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_view rv{hamon::move(r), 3};
#else
	hamon::ranges::take_view<R> rv{hamon::move(r), 3};
#endif
	auto const& crv = rv;

	static_assert( hamon::same_as_t<decltype(rv.begin()), hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   hamon::counted_iterator<decltype(r.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(rv.end().base()), decltype(r.end())>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(crv.end()),   hamon::counted_iterator<decltype(cr.begin())>>::value, "");
	static_assert(!hamon::same_as_t<decltype(crv.end()),   hamon::default_sentinel_t>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.end().base()), decltype(cr.end())>::value, "");

	{
		using Iter  = decltype(rv.begin());
		using CIter = decltype(crv.begin());
		using Sent  = decltype(rv.end());
		using CSent = decltype(crv.end());

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

	using Sentinel = decltype(rv.end());
	using ConstSentinel = decltype(crv.end());
	static_assert(!hamon::same_as_t<Sentinel, ConstSentinel>::value, "");
	static_assert(!hamon::constructible_from_t<Sentinel, ConstSentinel>::value, "");
	static_assert( hamon::constructible_from_t<ConstSentinel, Sentinel>::value, "");

	{
		Sentinel s{};
		VERIFY(rv.begin() != s);
		VERIFY(crv.begin() != s);
	}
	{
		ConstSentinel cs{};
		VERIFY(rv.begin() != cs);
		VERIFY(crv.begin() != cs);
	}

	Sentinel s = rv.end();
	ConstSentinel cs = s;

	auto it = rv.begin();
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
		auto rv = r | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<R>>::value, "");
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(rv.base().end() == r.end());
		VERIFY(rv.size() == 3);

		auto rv2 = hamon::views::take(r, 3);
		static_assert( hamon::same_as_t<decltype(rv), decltype(rv2)>::value, "");
	}
	{
		auto rv = a | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<hamon::ranges::ref_view<int[9]>>>::value, "");
		VERIFY(rv.base().begin() == a);
		VERIFY(rv.base().end() == a + 9);
		VERIFY(rv.size() == 3);

		auto rv2 = hamon::views::take(a, 3);
		static_assert( hamon::same_as_t<decltype(rv), decltype(rv2)>::value, "");
	}
	{
		auto rv = a | hamon::views::take(5) | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<hamon::ranges::take_view<hamon::ranges::ref_view<int[9]>>>>::value, "");
		VERIFY(rv.base().base().begin() == a);
		VERIFY(rv.base().base().end() == a + 9);
		VERIFY(rv.size() == 3);
		VERIFY(*rv.begin() == 1);

		auto rv2 = hamon::views::take(hamon::views::take(a, 5), 3);
		static_assert( hamon::same_as_t<decltype(rv), decltype(rv2)>::value, "");
	}

	struct Double
	{
		constexpr int operator()(int x) const
		{
			return x * 2;
		}
	};

	{
		auto rv = a | hamon::views::transform(Double{}) | hamon::views::take(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<hamon::ranges::transform_view<hamon::ranges::ref_view<int[9]>, Double>>>::value, "");
		VERIFY(rv.size() == 4);
		VERIFY(*rv.begin() == 2);
	}
	{
		auto rv = a | hamon::views::take(4) | hamon::views::transform(Double{});
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::transform_view<hamon::ranges::take_view<hamon::ranges::ref_view<int[9]>>, Double>>::value, "");
		VERIFY(rv.size() == 4);
		VERIFY(*rv.begin() == 2);
	}
	{
		auto partial = hamon::views::transform(Double{}) | hamon::views::take(4);
		auto rv = a | partial;
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<hamon::ranges::transform_view<hamon::ranges::ref_view<int[9]>, Double>>>::value, "");
		VERIFY(rv.size() == 4);
		VERIFY(*rv.begin() == 2);
	}

	{
		hamon::ranges::empty_view<int> r;
		auto rv = r | hamon::views::take(5);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::empty_view<int>>::value, "");
		VERIFY(rv.size() == 0);
	}
	{
		hamon::span<int> s(a);
		auto rv = s | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::span<int>>::value, "");
		VERIFY(rv.size() == 3);
	}
	{
		hamon::span<int, 9> s(a);
		auto rv = s | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::span<int, hamon::dynamic_extent>>::value, "");
		VERIFY(rv.size() == 3);
	}
	{
		hamon::string_view sv = "abcdefg";
		auto rv = sv | hamon::views::take(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::string_view>::value, "");
		VERIFY(rv.size() == 4);
	}
	{
		hamon::ranges::subrange<int*> s(a, a + 5);
		auto rv = s | hamon::views::take(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::subrange<int*>>::value, "");
		VERIFY(rv.size() == 4);
	}
	{
		using R = test_forward_sized_view<int>;
		using I = hamon::ranges::iterator_t<R>;
		using S = hamon::ranges::sentinel_t<R>;
		R r(a);
		hamon::ranges::subrange<I, S> s(r.begin(), r.end());
		auto rv = s | hamon::views::take(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<decltype(s)>>::value, "");
		static_assert(has_size<decltype(rv)>::value == false, "");
	}
	{
		auto rv = hamon::views::iota(1, 8) | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::iota_view<int, int>>::value, "");
		VERIFY(rv.size() == 3);
		VERIFY(*rv.begin() == 1);
	}
	{
		auto rv = hamon::views::iota(1) | hamon::views::take(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::take_view<hamon::ranges::iota_view<int, hamon::unreachable_sentinel_t>>>::value, "");
		static_assert(has_size<decltype(rv)>::value == false, "");
		VERIFY(*rv.begin() == 1);
	}
	{
		auto rv = hamon::views::repeat(42, 8) | hamon::views::take(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::repeat_view<int, int>>::value, "");
		VERIFY(rv.size() == 4);
		VERIFY(*rv.begin() == 42);
	}
	{
		auto rv = hamon::views::repeat(42) | hamon::views::take(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::repeat_view<int, hamon::ranges::range_difference_t<decltype(hamon::views::repeat(42))>>>::value, "");
		VERIFY(rv.size() == 4);
		VERIFY(*rv.begin() == 42);
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
