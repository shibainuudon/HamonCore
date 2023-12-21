/**
 *	@file	unit_test_ranges_take_while.cpp
 *
 *	@brief	ranges::take_while_view のテスト
 */

#include <hamon/ranges/adaptors/take_while_view.hpp>
#include <hamon/ranges/adaptors/filter_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/algorithm/ranges.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace take_while_test
{

struct IsZero
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const HAMON_NOEXCEPT
	{
		return x == 0;
	}
};

struct VoidFunc
{
	HAMON_CXX14_CONSTEXPR void operator()(int) const HAMON_NOEXCEPT
	{
	}
};

struct LessThanFive
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const HAMON_NOEXCEPT
	{
		return x < 5;
	}
};

HAMON_CXX11_CONSTEXPR bool IsEven(int x)
{
	return x % 2 == 0;
}

template <typename T>
struct ConstNotView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   noexcept { return nullptr; }
};

struct Empty{};

template <typename T>
struct NotSimpleView1 : hamon::ranges::view_base
{
	HAMON_CXX14_CONSTEXPR T*     begin()       noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR Empty* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR T*     end()         noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR Empty* end()   const noexcept { return nullptr; }
};
static_assert(hamon::ranges::view_t<NotSimpleView1<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleView1<int>>::value, "");

template <typename T>
struct NotSimpleView2 : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleView2(T (&arr)[N]) : NotSimpleView2(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleView2(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR T*       begin()       noexcept { return m_first; }
	HAMON_CXX11_CONSTEXPR T const* begin() const noexcept { return m_first; }
	HAMON_CXX14_CONSTEXPR T*       end()         noexcept { return m_last; }
	HAMON_CXX11_CONSTEXPR T const* end()   const noexcept { return m_last; }
};
static_assert(hamon::ranges::view_t<NotSimpleView2<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleView2<int>>::value, "");

template <typename T>
struct NotSimpleForwardView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = forward_iterator_wrapper<T>;
	using const_iterator = forward_iterator_wrapper<T const>;
	using sentinel = test_sentinel<iterator>;
	using const_sentinel = test_sentinel<const_iterator>;

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleForwardView(T (&arr)[N]) : NotSimpleForwardView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleForwardView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};
static_assert(hamon::ranges::view_t<NotSimpleForwardView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleForwardView<int>>::value, "");

template <typename T>
struct MoveOnlyView : hamon::ranges::view_base
{
	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};
static_assert(hamon::ranges::view_t<MoveOnlyView<int>>::value, "");
static_assert(!hamon::copyable_t<MoveOnlyView<int>>::value, "");

template <typename T, typename Pred, typename = void>
struct CanInstantiateTakeWhileView
	: hamon::false_type {};

template <typename T, typename Pred>
struct CanInstantiateTakeWhileView<T, Pred, hamon::void_t<hamon::ranges::take_while_view<T, Pred>>>
	: hamon::true_type {};

static_assert( CanInstantiateTakeWhileView<test_input_view<int>, IsZero>::value, "");
static_assert( CanInstantiateTakeWhileView<test_input_view<int>, LessThanFive>::value, "");
static_assert( CanInstantiateTakeWhileView<test_input_view<int>, decltype(&IsEven)>::value, "");
static_assert(!CanInstantiateTakeWhileView<test_input_view<int>, VoidFunc>::value, "");	// indirect_unary_predicate
static_assert( CanInstantiateTakeWhileView<ConstNotView<int>, IsZero>::value, "");
static_assert( CanInstantiateTakeWhileView<NotSimpleView1<int>, IsZero>::value, "");
static_assert( CanInstantiateTakeWhileView<NotSimpleView2<int>, IsZero>::value, "");
static_assert( CanInstantiateTakeWhileView<NotSimpleForwardView<int>, IsZero>::value, "");
static_assert( CanInstantiateTakeWhileView<MoveOnlyView<int>, IsZero>::value, "");
static_assert(!CanInstantiateTakeWhileView<test_input_range<int>, IsZero>::value, "");	// view<V>
static_assert(!CanInstantiateTakeWhileView<test_output_view<int>, IsZero>::value, "");	// input_range<V>
static_assert(!CanInstantiateTakeWhileView<test_input_view<int*>, IsZero>::value, "");	// indirect_unary_predicate<const Pred, iterator_t<V>>
static_assert(!CanInstantiateTakeWhileView<test_input_view<int>, IsZero&>::value, "");	// is_object_v<Pred>

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View, typename F>
HAMON_CXX14_CONSTEXPR bool test00_impl()
{
	using T = int;
	using V = View<T>;
	using RV = hamon::ranges::take_while_view<V, F>;

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == hamon::ranges::contiguous_range_t<V>::value, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");

	static_assert(hamon::is_default_constructible<RV>::value ==
		(hamon::is_default_constructible<V>::value && hamon::is_default_constructible<F>::value), "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value ==
		(hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<F>::value), "");

	static_assert(!hamon::is_constructible<RV, V>::value, "");
	static_assert(!hamon::is_constructible<RV, F>::value, "");
	static_assert( hamon::is_constructible<RV, V, F>::value, "");
	static_assert(!hamon::is_constructible<RV, F, V>::value, "");
	static_assert(!hamon::is_constructible<RV, V, F, F>::value, "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().base()), V>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible_t<V>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().base()), V>::value, "");
	}
#endif

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const>().pred()), F const&>::value, "");

	static_assert(has_begin<RV>::value, "");
	static_assert(has_end<RV>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::ranges::range_t<V const>::value)
	{
		using CI = hamon::ranges::iterator_t<V const>;
		static_assert(has_begin<RV const>::value == hamon::indirect_unary_predicate_t<F const, CI>::value, "");
		static_assert(has_end<RV const>::value   == hamon::indirect_unary_predicate_t<F const, CI>::value, "");

		if constexpr (has_begin<RV const>::value)
		{
			static_assert(hamon::same_as_t<
				decltype(hamon::declval<RV>().begin()),
				decltype(hamon::declval<RV const>().begin())>::value ==
				hamon::ranges::detail::simple_view_t<V>::value, "");
		}
		if constexpr (has_end<RV const>::value)
		{
			static_assert(hamon::same_as_t<
				decltype(hamon::declval<RV>().end()),
				decltype(hamon::declval<RV const>().end())>::value ==
				hamon::ranges::detail::simple_view_t<V>::value, "");
		}
	}
	else
	{
		static_assert(has_begin<RV const>::value == false, "");
		static_assert(has_end<RV const>::value   == false, "");
	}
#endif

	return true;
}

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	VERIFY((test00_impl<View, IsZero>()));
	VERIFY((test00_impl<View, LessThanFive>()));
	VERIFY((test00_impl<View, decltype(&IsEven)>()));
#if defined(HAMON_HAS_CXX20_LAMBDAS_IN_UNEVALUATED_CONTEXTS)
	VERIFY((test00_impl<View, decltype([](int){return false;})>()));
#endif
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	hamon::ranges::take_while_view<V, LessThanFive> rv{};

	VERIFY(rv.begin() == rv.end());
	VERIFY(rv.begin() == rv.base().begin());
	VERIFY(hamon::as_const(rv).begin() == hamon::as_const(rv).end());
	VERIFY(hamon::as_const(rv).begin() == rv.base().begin());

	{
		auto& p = rv.pred();
		static_assert(hamon::same_as_t<decltype(p), LessThanFive const&>::value, "");
	}
	{
		auto b = rv.base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(b.begin() == b.end());
	}
	{
		auto b = hamon::move(rv).base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(b.begin() == b.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};

	using V = test_input_view<int>;
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_while_view rv{v, LessThanFive{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::take_while_view<V, LessThanFive>>::value, "");
#else
	hamon::ranges::take_while_view<V, LessThanFive> rv{v, LessThanFive{}};
#endif
	auto const& crv = rv;

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

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};

	using V = NotSimpleView2<int>;
	V v(a);
	auto const& cv = v;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_while_view rv{v, LessThanFive{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::take_while_view<V, LessThanFive>>::value, "");
#else
	hamon::ranges::take_while_view<V, LessThanFive> rv{v, LessThanFive{}};
#endif
	auto const& crv = rv;

	{
		auto it = rv.begin();

		VERIFY(!(it == crv.end()));
		VERIFY( (it != crv.end()));
		VERIFY(!(crv.end() == it));
		VERIFY( (crv.end() != it));
		VERIFY(!(it == rv.end()));
		VERIFY( (it != rv.end()));
		VERIFY(!(rv.end() == it));
		VERIFY( (rv.end() != it));

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

		VERIFY( (it == crv.end()));
		VERIFY(!(it != crv.end()));
		VERIFY( (crv.end() == it));
		VERIFY(!(crv.end() != it));
		VERIFY( (it == rv.end()));
		VERIFY(!(it != rv.end()));
		VERIFY( (rv.end() == it));
		VERIFY(!(rv.end() != it));
	}
	{
		auto it = crv.begin();

		VERIFY(!(it == crv.end()));
		VERIFY( (it != crv.end()));
		VERIFY(!(crv.end() == it));
		VERIFY( (crv.end() != it));
		VERIFY(!(it == rv.end()));
		VERIFY( (it != rv.end()));
		VERIFY(!(rv.end() == it));
		VERIFY( (rv.end() != it));

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
		VERIFY(it == rv.end());

		VERIFY( (it == crv.end()));
		VERIFY(!(it != crv.end()));
		VERIFY( (crv.end() == it));
		VERIFY(!(crv.end() != it));
		VERIFY( (it == rv.end()));
		VERIFY(!(it != rv.end()));
		VERIFY( (rv.end() == it));
		VERIFY(!(rv.end() != it));
	}

	using Iterator = decltype(rv.begin());
	using ConstIterator = decltype(crv.begin());
	using Sentinel = decltype(rv.end());
	using ConstSentinel = decltype(crv.end());
	static_assert(!hamon::same_as_t<Sentinel, ConstSentinel>::value, "");
	static_assert(!hamon::constructible_from_t<Sentinel, ConstSentinel>::value, "");
	static_assert( hamon::constructible_from_t<ConstSentinel, Sentinel>::value, "");

	static_assert( has_eq <Iterator, Iterator>::value, "");
	static_assert( has_eq <Iterator, ConstIterator>::value, "");
	static_assert( has_eq <Iterator, Sentinel>::value, "");
	static_assert( has_eq <Iterator, ConstSentinel>::value, "");
	static_assert( has_neq<Iterator, Iterator>::value, "");
	static_assert( has_neq<Iterator, ConstIterator>::value, "");
	static_assert( has_neq<Iterator, Sentinel>::value, "");
	static_assert( has_neq<Iterator, ConstSentinel>::value, "");

	static_assert( has_eq <ConstIterator, Iterator>::value, "");
	static_assert( has_eq <ConstIterator, ConstIterator>::value, "");
	static_assert( has_eq <ConstIterator, Sentinel>::value, "");
	static_assert( has_eq <ConstIterator, ConstSentinel>::value, "");
	static_assert( has_neq<ConstIterator, Iterator>::value, "");
	static_assert( has_neq<ConstIterator, ConstIterator>::value, "");
	static_assert( has_neq<ConstIterator, Sentinel>::value, "");
	static_assert( has_neq<ConstIterator, ConstSentinel>::value, "");

	static_assert( has_eq <Sentinel, Iterator>::value, "");
	static_assert( has_eq <Sentinel, ConstIterator>::value, "");
	static_assert(!has_eq <Sentinel, Sentinel>::value, "");
	static_assert(!has_eq <Sentinel, ConstSentinel>::value, "");
	static_assert( has_neq<Sentinel, Iterator>::value, "");
	static_assert( has_neq<Sentinel, ConstIterator>::value, "");
	static_assert(!has_neq<Sentinel, Sentinel>::value, "");
	static_assert(!has_neq<Sentinel, ConstSentinel>::value, "");

	static_assert( has_eq <ConstSentinel, Iterator>::value, "");
	static_assert( has_eq <ConstSentinel, ConstIterator>::value, "");
	static_assert(!has_eq <ConstSentinel, Sentinel>::value, "");
	static_assert(!has_eq <ConstSentinel, ConstSentinel>::value, "");
	static_assert( has_neq<ConstSentinel, Iterator>::value, "");
	static_assert( has_neq<ConstSentinel, ConstIterator>::value, "");
	static_assert(!has_neq<ConstSentinel, Sentinel>::value, "");
	static_assert(!has_neq<ConstSentinel, ConstSentinel>::value, "");

	{
		Sentinel sent{};
		VERIFY(sent.base() == nullptr);
	}
	{
		ConstSentinel sent{};
		VERIFY(sent.base() == nullptr);
	}
	{
		static_assert(hamon::same_as_t<decltype(rv.end().base()), decltype(v.end())>::value, "");
		static_assert(hamon::same_as_t<decltype(crv.end().base()), decltype(cv.end())>::value, "");

		auto sent = crv.end();
		VERIFY(sent.base() == rv.end());
		sent = rv.end();
		VERIFY(sent.base() == rv.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};

	using V = NotSimpleForwardView<int>;
	V v(a);
	//auto const& cv = v;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::take_while_view rv{v, LessThanFive{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::take_while_view<V, LessThanFive>>::value, "");
#else
	hamon::ranges::take_while_view<V, LessThanFive> rv{v, LessThanFive{}};
#endif
	auto const& crv = rv;

	using Iterator = decltype(rv.begin());
	using ConstIterator = decltype(crv.begin());
	using Sentinel = decltype(rv.end());
	using ConstSentinel = decltype(crv.end());
	static_assert(!hamon::same_as_t<Sentinel, ConstSentinel>::value, "");
	static_assert(!hamon::constructible_from_t<Sentinel, ConstSentinel>::value, "");
	static_assert(!hamon::constructible_from_t<ConstSentinel, Sentinel>::value, "");

	static_assert( has_eq <Iterator, Iterator>::value, "");
	static_assert(!has_eq <Iterator, ConstIterator>::value, "");
	static_assert( has_eq <Iterator, Sentinel>::value, "");
	static_assert(!has_eq <Iterator, ConstSentinel>::value, "");
	static_assert( has_neq<Iterator, Iterator>::value, "");
	static_assert(!has_neq<Iterator, ConstIterator>::value, "");
	static_assert( has_neq<Iterator, Sentinel>::value, "");
	static_assert(!has_neq<Iterator, ConstSentinel>::value, "");

	static_assert(!has_eq <ConstIterator, Iterator>::value, "");
	static_assert( has_eq <ConstIterator, ConstIterator>::value, "");
	static_assert(!has_eq <ConstIterator, Sentinel>::value, "");
	static_assert( has_eq <ConstIterator, ConstSentinel>::value, "");
	static_assert(!has_neq<ConstIterator, Iterator>::value, "");
	static_assert( has_neq<ConstIterator, ConstIterator>::value, "");
	static_assert(!has_neq<ConstIterator, Sentinel>::value, "");
	static_assert( has_neq<ConstIterator, ConstSentinel>::value, "");

	static_assert( has_eq <Sentinel, Iterator>::value, "");
	static_assert(!has_eq <Sentinel, ConstIterator>::value, "");
	static_assert(!has_eq <Sentinel, Sentinel>::value, "");
	static_assert(!has_eq <Sentinel, ConstSentinel>::value, "");
	static_assert( has_neq<Sentinel, Iterator>::value, "");
	static_assert(!has_neq<Sentinel, ConstIterator>::value, "");
	static_assert(!has_neq<Sentinel, Sentinel>::value, "");
	static_assert(!has_neq<Sentinel, ConstSentinel>::value, "");

	static_assert(!has_eq <ConstSentinel, Iterator>::value, "");
	static_assert( has_eq <ConstSentinel, ConstIterator>::value, "");
	static_assert(!has_eq <ConstSentinel, Sentinel>::value, "");
	static_assert(!has_eq <ConstSentinel, ConstSentinel>::value, "");
	static_assert(!has_neq<ConstSentinel, Iterator>::value, "");
	static_assert( has_neq<ConstSentinel, ConstIterator>::value, "");
	static_assert(!has_neq<ConstSentinel, Sentinel>::value, "");
	static_assert(!has_neq<ConstSentinel, ConstSentinel>::value, "");

	return true;
}

HAMON_CXX17_CONSTEXPR bool test05()
{
	{
		int buf[5] {};
		hamon::ranges::copy(
			hamon::views::iota(1) | hamon::views::take_while([](int x){ return x < 4; }),
			buf);
		VERIFY(buf[0] == 1);
		VERIFY(buf[1] == 2);
		VERIFY(buf[2] == 3);
		VERIFY(buf[3] == 0);
		VERIFY(buf[4] == 0);
	}
	{
		int buf[10] {};
		int a[] = { 3, 1, 4, 1, 5, 9 };
		hamon::ranges::copy(
			a | hamon::views::take_while([](int x){ return x != 0; }),
			buf);
		VERIFY(buf[0] == 3);
		VERIFY(buf[1] == 1);
		VERIFY(buf[2] == 4);
		VERIFY(buf[3] == 1);
		VERIFY(buf[4] == 5);
		VERIFY(buf[5] == 9);
		VERIFY(buf[6] == 0);
	}
	{
		int a[] = { 8, 2, 4, 5, 0, 1, 2 };
		auto rv = hamon::views::take_while(IsEven)(a);
		auto it = rv.begin();
		VERIFY(*it++ == 8);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(it == rv.end());
	}
	{
		auto rv = hamon::views::take_while(
			hamon::views::iota(1),
			[](int x) { return x < 10; });
		auto it = rv.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 7);
		VERIFY(*it++ == 8);
		VERIFY(*it++ == 9);
		VERIFY(it == rv.end());
	}

	// C++20以前は、ラムダ式のクロージャオブジェクトが代入可能でなかったので、
	// Range Adaptorを連結するには、ラムダ式以外にしたり一時変数に受けたりしないといけなかった。
	{
		auto rv = hamon::views::iota(1) |
			hamon::views::filter(IsEven) |
			hamon::views::take_while([](int x) { return x < 10; });
		auto it = rv.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 8);
		VERIFY(it == rv.end());
	}
	{
		auto rv = hamon::views::iota(1) | hamon::views::filter([](int x) { return x % 2 == 0; });
		auto rv2 = rv | hamon::views::take_while([](int x) { return x < 10; });
		auto it = rv2.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 8);
		VERIFY(it == rv2.end());
	}
	{
		auto partial =
			hamon::views::filter(IsEven) |
			hamon::views::take_while([](int x) { return x < 10; });
		auto rv = hamon::views::iota(1) | partial;
		auto it = rv.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 8);
		VERIFY(it == rv.end());
	}
#if defined(HAMON_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS)
	// C++20(P0624R2) で、ラムダ式のクロージャオブジェクトが代入可能になったので、
	// 以下のようにラムダ式を含むRange Adaptorを素直に連結できるようになった。
	{
		auto rv = hamon::views::iota(1) |
			hamon::views::filter([](int x) { return x % 2 == 0; }) |
			hamon::views::take_while([](int x) { return x < 10; });
		auto it = rv.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 8);
		VERIFY(it == rv.end());
	}
	{
		auto partial =
			hamon::views::filter([](int x) { return x % 2 == 0; }) |
			hamon::views::take_while([](int x) { return x < 10; });
		auto rv = hamon::views::iota(1) | partial;
		auto it = rv.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 8);
		VERIFY(it == rv.end());
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, TakeWhileTest)
{
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

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<ConstNotView>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NotSimpleView1>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NotSimpleView2>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<NotSimpleForwardView>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<MoveOnlyView>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(test05());

#if 0	// TODO
	// [range.take.while.overview]/3
	// Example 1:
	{
		auto input = std::istringstream {"0 1 2 3 4 5 6 7 8 9"};
		auto small = [](const auto x) noexcept { return x < 5; };
		auto small_ints = hamon::views::istream<int>(input) | hamon::views::take_while(small);
		for (const auto i : small_ints)
		{
			std::cout << i << ' ';                             // prints 0 1 2 3 4
		}
		auto i = 0;
		input >> i;
		std::cout << i;                                      // prints 6
	}
#endif
}

}	// namespace take_while_test
}	// namespace hamon_ranges_test
