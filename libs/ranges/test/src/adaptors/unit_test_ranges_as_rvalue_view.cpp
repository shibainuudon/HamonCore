/**
 *	@file	unit_test_ranges_as_rvalue_view.cpp
 *
 *	@brief	ranges::as_rvalue_view のテスト
 */

#include <hamon/ranges/adaptors/as_rvalue_view.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_rvalue_view_test
{

template <typename T, typename = void>
struct CanInstantiateAsRvalueView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateAsRvalueView<T, hamon::void_t<hamon::ranges::as_rvalue_view<T>>>
	: hamon::true_type {};

static_assert(!CanInstantiateAsRvalueView<int>::value, "");
static_assert( CanInstantiateAsRvalueView<test_input_view<int>>::value, "");
static_assert( CanInstantiateAsRvalueView<test_input_common_view<int>>::value, "");
static_assert(!CanInstantiateAsRvalueView<test_input_view<int> const>::value, "");		// cv修飾がついてはいけない
static_assert(!CanInstantiateAsRvalueView<test_input_view<int> volatile>::value, "");	// cv修飾がついてはいけない
static_assert(!CanInstantiateAsRvalueView<test_input_range<int>>::value, "");			// viewでなければいけない
static_assert(!CanInstantiateAsRvalueView<test_output_view<int>>::value, "");			// input_rangeでなければいけない

template <typename T>
struct NotSimpleView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = T*;
	using const_iterator = T const*;
	using sentinel = test_sentinel<iterator>;
	using const_sentinel = test_sentinel<const_iterator>;

	template <hamon::size_t N>
	explicit HAMON_CONSTEXPR NotSimpleView(T (&arr)[N]) : NotSimpleView(arr, arr+N) {}

	HAMON_CONSTEXPR NotSimpleView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

static_assert(hamon::ranges::view<NotSimpleView<int>>, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleView<int>>::value, "");

template <typename T>
struct NotSimpleViewCommonRange : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = T*;
	using const_iterator = T const*;
	using sentinel = T*;
	using const_sentinel = T const*;

	template <hamon::size_t N>
	explicit HAMON_CONSTEXPR NotSimpleViewCommonRange(T (&arr)[N]) : NotSimpleViewCommonRange(arr, arr+N) {}

	HAMON_CONSTEXPR NotSimpleViewCommonRange(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

static_assert(hamon::ranges::view<NotSimpleViewCommonRange<int>>, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleViewCommonRange<int>>::value, "");
static_assert(hamon::ranges::range<NotSimpleViewCommonRange<int>>, "");
static_assert(hamon::ranges::common_range<NotSimpleViewCommonRange<int>>, "");

template <typename T>
struct ConstNotView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   noexcept { return nullptr; }
};

static_assert(hamon::ranges::view<ConstNotView<int>>, "");
static_assert(!hamon::ranges::detail::simple_view_t<ConstNotView<int>>::value, "");
static_assert( hamon::ranges::range<ConstNotView<int>>, "");
static_assert(!hamon::ranges::range<ConstNotView<int> const>, "");

template <typename T>
struct NonCopyableView : hamon::ranges::view_base
{
	NonCopyableView(NonCopyableView const&) = delete;
	NonCopyableView(NonCopyableView &&) = default;
	NonCopyableView& operator=(NonCopyableView const&) = delete;
	NonCopyableView& operator=(NonCopyableView &&) = default;

	HAMON_CXX14_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

static_assert(hamon::ranges::view<NonCopyableView<int>>, "");
static_assert(hamon::ranges::detail::simple_view_t<NonCopyableView<int>>::value, "");
static_assert(!hamon::copy_constructible<NonCopyableView<int>>, "");

template <typename T>
struct ThrowOnCopyView : hamon::ranges::view_base
{
	ThrowOnCopyView(ThrowOnCopyView const&) noexcept(false) {}
	ThrowOnCopyView(ThrowOnCopyView &&) = default;
	ThrowOnCopyView& operator=(ThrowOnCopyView const&) = default;
	ThrowOnCopyView& operator=(ThrowOnCopyView &&) = default;

	HAMON_CXX14_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

static_assert(hamon::ranges::view<ThrowOnCopyView<int>>, "");
static_assert(hamon::ranges::detail::simple_view_t<ThrowOnCopyView<int>>::value, "");
static_assert(hamon::is_move_constructible<ThrowOnCopyView<int>>::value, "");
static_assert(!hamon::is_nothrow_copy_constructible<ThrowOnCopyView<int>>::value, "");
static_assert( hamon::is_nothrow_move_constructible<ThrowOnCopyView<int>>::value, "");

template <typename T>
struct ThrowOnMoveView : hamon::ranges::view_base
{
	ThrowOnMoveView(ThrowOnMoveView const&) = default;
	ThrowOnMoveView(ThrowOnMoveView &&) noexcept(false) {};
	ThrowOnMoveView& operator=(ThrowOnMoveView const&) = default;
	ThrowOnMoveView& operator=(ThrowOnMoveView &&) = default;

	HAMON_CXX14_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

static_assert(hamon::ranges::view<ThrowOnMoveView<int>>, "");
static_assert(hamon::ranges::detail::simple_view_t<ThrowOnMoveView<int>>::value, "");
static_assert(hamon::is_move_constructible<ThrowOnMoveView<int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<ThrowOnMoveView<int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<ThrowOnMoveView<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using ARV = hamon::ranges::as_rvalue_view<V>;

	static_assert(hamon::is_default_constructible<ARV>::value == hamon::is_default_constructible<V>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<ARV>::value == hamon::is_nothrow_default_constructible<V>::value, "");

	static_assert(hamon::is_constructible<ARV, V>::value, "");
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
	static_assert(hamon::is_nothrow_constructible<ARV, V>::value == hamon::is_nothrow_move_constructible<V>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<ARV, V>::value, "");

	static_assert( hamon::ranges::range<ARV>, "");
	static_assert( hamon::ranges::borrowed_range<ARV> == hamon::ranges::borrowed_range<V>, "");
	static_assert( hamon::ranges::sized_range<ARV> == hamon::ranges::sized_range<V>, "");
	static_assert( hamon::ranges::approximately_sized_range<ARV> == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(!hamon::ranges::output_range<ARV, T>, "");
	static_assert( hamon::ranges::input_range<ARV> == hamon::ranges::input_range<V>, "");
	static_assert( hamon::ranges::forward_range<ARV> == hamon::ranges::forward_range<V>, "");
	static_assert( hamon::ranges::bidirectional_range<ARV> == hamon::ranges::bidirectional_range<V>, "");
	static_assert( hamon::ranges::random_access_range<ARV> == hamon::ranges::random_access_range<V>, "");
	static_assert(!hamon::ranges::contiguous_range<ARV>, "");
	static_assert( hamon::ranges::common_range<ARV> == hamon::ranges::common_range<V>, "");
	static_assert( hamon::ranges::viewable_range<ARV>, "");
	static_assert( hamon::ranges::view<ARV>, "");
	static_assert(!hamon::ranges::constant_range<ARV>, "");

	static_assert(has_base<ARV&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<ARV&&>::value, "");
	static_assert(has_base<ARV const&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<ARV const&&>::value == hamon::copy_constructible<V>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<ARV&&>().base()), V>, "");
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
	static_assert(noexcept(hamon::declval<ARV&&>().base()) == hamon::is_nothrow_move_constructible<V>::value, "");
#endif

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible<V>)
	{
		static_assert(hamon::same_as<decltype(hamon::declval<ARV&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<ARV const&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<ARV const&&>().base()), V>, "");
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
		static_assert(noexcept(hamon::declval<ARV&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
#endif
	}
#endif

	{
		using I = decltype(hamon::ranges::begin(hamon::declval<V&>()));

		static_assert(hamon::same_as<decltype(hamon::declval<ARV&>().begin()), hamon::move_iterator<I>>, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (hamon::ranges::common_range<V>)
		{
			static_assert(hamon::same_as<decltype(hamon::declval<ARV&>().end()), hamon::move_iterator<I>>, "");
		}
		else
		{
			using S = decltype(hamon::ranges::end(hamon::declval<V&>()));
			static_assert(hamon::same_as<decltype(hamon::declval<ARV&>().end()), hamon::move_sentinel<S>>, "");
		}
#endif

#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
		static_assert(noexcept(hamon::declval<ARV&>().begin()) == noexcept(hamon::ranges::begin(hamon::declval<V&>())), "");
		static_assert(noexcept(hamon::declval<ARV&>().end()) == noexcept(hamon::ranges::end(hamon::declval<V&>())), "");
#endif
	}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::ranges::range<V const>)
	{
		using CI = decltype(hamon::ranges::begin(hamon::declval<V const&>()));
		using CS = decltype(hamon::ranges::end(hamon::declval<V const&>()));

		static_assert(hamon::same_as<decltype(hamon::declval<ARV const&>().begin()), hamon::move_iterator<CI>>, "");

		if constexpr (hamon::ranges::common_range<V const>)
		{
			static_assert(hamon::same_as<decltype(hamon::declval<ARV const&>().end()), hamon::move_iterator<CI>>, "");
		}
		else
		{
			static_assert(hamon::same_as<decltype(hamon::declval<ARV const&>().end()), hamon::move_sentinel<CS>>, "");
		}

#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
		static_assert(noexcept(hamon::declval<ARV const&>().begin()), "");
		static_assert(noexcept(hamon::declval<ARV const&>().end()), "");
#endif
	}
#endif

	static_assert(has_begin<ARV>::value, "");
	static_assert(has_begin<ARV const>::value == hamon::ranges::range<V const>, "");

	static_assert(has_end<ARV>::value, "");
	static_assert(has_end<ARV const>::value == hamon::ranges::range<V const>, "");

	static_assert(has_size<ARV>::value == hamon::ranges::sized_range<V>, "");
	static_assert(has_size<ARV const>::value == hamon::ranges::sized_range<V const>, "");

	static_assert(has_reserve_hint<ARV>::value == hamon::ranges::approximately_sized_range<V>, "");
	static_assert(has_reserve_hint<ARV const>::value == hamon::ranges::approximately_sized_range<V const>, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
	if constexpr (has_size<ARV>::value)
	{
		static_assert(noexcept(hamon::declval<ARV&>().size()) == noexcept(hamon::ranges::size(hamon::declval<V&>())), "");
	}

	if constexpr (has_size<ARV const>::value)
	{
		static_assert(noexcept(hamon::declval<ARV const&>().size()) == noexcept(hamon::ranges::size(hamon::declval<V const&>())), "");
	}
#endif
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_random_access_view<int>;
	using ARV = hamon::ranges::as_rvalue_view<R>;

	static_assert( has_begin<ARV&>::value, "");
	static_assert( has_end<ARV&>::value, "");
	static_assert( has_empty<ARV&>::value, "");
	static_assert( has_cbegin<ARV&>::value, "");
	static_assert( has_cend<ARV&>::value, "");
	static_assert( has_operator_bool<ARV&>::value, "");
	static_assert(!has_data<ARV&>::value, "");
	static_assert( has_size<ARV&>::value, "");
	static_assert( has_reserve_hint<ARV&>::value, "");
	static_assert( has_front<ARV&>::value, "");
	static_assert(!has_back<ARV&>::value, "");
	static_assert( has_subscript<ARV&>::value, "");
	static_assert( has_base<ARV&>::value, "");

	static_assert( has_begin<ARV const&>::value, "");
	static_assert( has_end<ARV const&>::value, "");
	static_assert( has_empty<ARV const&>::value, "");
	static_assert( has_cbegin<ARV const&>::value, "");
	static_assert( has_cend<ARV const&>::value, "");
	static_assert( has_operator_bool<ARV const&>::value, "");
	static_assert(!has_data<ARV const&>::value, "");
	static_assert( has_size<ARV const&>::value, "");
	static_assert( has_reserve_hint<ARV const&>::value, "");
	static_assert( has_front<ARV const&>::value, "");
	static_assert(!has_back<ARV const&>::value, "");
	static_assert( has_subscript<ARV const&>::value, "");
	static_assert( has_base<ARV const&>::value, "");

	int a[2] = {1, 2};
	R r(a);

	{
		ARV arv{};
		VERIFY(arv.empty());
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV>, "");
#else
		ARV arv{r};
#endif
		VERIFY(!arv.empty());
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.size() == 2);
		VERIFY(arv.reserve_hint() == 2);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV const>, "");
#else
		ARV const arv{r};
#endif
		VERIFY(!arv.empty());
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.size() == 2);
		VERIFY(arv.reserve_hint() == 2);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using R = NotSimpleView<int>;
	using ARV = hamon::ranges::as_rvalue_view<R>;

	static_assert( has_begin<ARV&>::value, "");
	static_assert( has_end<ARV&>::value, "");
	static_assert( has_empty<ARV&>::value, "");
	static_assert( has_cbegin<ARV&>::value, "");
	static_assert( has_cend<ARV&>::value, "");
	static_assert( has_operator_bool<ARV&>::value, "");
	static_assert(!has_data<ARV&>::value, "");
	static_assert( has_size<ARV&>::value, "");
	static_assert( has_reserve_hint<ARV&>::value, "");
	static_assert( has_front<ARV&>::value, "");
	static_assert(!has_back<ARV&>::value, "");
	static_assert( has_subscript<ARV&>::value, "");
	static_assert( has_base<ARV&>::value, "");

	static_assert( has_begin<ARV const&>::value, "");
	static_assert( has_end<ARV const&>::value, "");
	static_assert( has_empty<ARV const&>::value, "");
	static_assert( has_cbegin<ARV const&>::value, "");
	static_assert( has_cend<ARV const&>::value, "");
	static_assert( has_operator_bool<ARV const&>::value, "");
	static_assert(!has_data<ARV const&>::value, "");
	static_assert( has_size<ARV const&>::value, "");
	static_assert( has_reserve_hint<ARV const&>::value, "");
	static_assert( has_front<ARV const&>::value, "");
	static_assert(!has_back<ARV const&>::value, "");
	static_assert( has_subscript<ARV const&>::value, "");
	static_assert( has_base<ARV const&>::value, "");

	int a[] = {1, 2, 3};
	R r(a);

	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV>, "");
#else
		ARV arv{r};
#endif
		VERIFY(!arv.empty());
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.size() == 3);
		VERIFY(arv.reserve_hint() == 3);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV const>, "");
#else
		ARV const arv{r};
#endif
		VERIFY(!arv.empty());
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.size() == 3);
		VERIFY(arv.reserve_hint() == 3);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using R = NotSimpleViewCommonRange<int>;
	using ARV = hamon::ranges::as_rvalue_view<R>;

	static_assert( has_begin<ARV&>::value, "");
	static_assert( has_end<ARV&>::value, "");
	static_assert( has_empty<ARV&>::value, "");
	static_assert( has_cbegin<ARV&>::value, "");
	static_assert( has_cend<ARV&>::value, "");
	static_assert( has_operator_bool<ARV&>::value, "");
	static_assert(!has_data<ARV&>::value, "");
	static_assert( has_size<ARV&>::value, "");
	static_assert( has_reserve_hint<ARV&>::value, "");
	static_assert( has_front<ARV&>::value, "");
	static_assert( has_back<ARV&>::value, "");
	static_assert( has_subscript<ARV&>::value, "");
	static_assert( has_base<ARV&>::value, "");

	static_assert( has_begin<ARV const&>::value, "");
	static_assert( has_end<ARV const&>::value, "");
	static_assert( has_empty<ARV const&>::value, "");
	static_assert( has_cbegin<ARV const&>::value, "");
	static_assert( has_cend<ARV const&>::value, "");
	static_assert( has_operator_bool<ARV const&>::value, "");
	static_assert(!has_data<ARV const&>::value, "");
	static_assert( has_size<ARV const&>::value, "");
	static_assert( has_reserve_hint<ARV const&>::value, "");
	static_assert( has_front<ARV const&>::value, "");
	static_assert( has_back<ARV const&>::value, "");
	static_assert( has_subscript<ARV const&>::value, "");
	static_assert( has_base<ARV const&>::value, "");

	int a[] = {1, 2, 3, 4};
	R r(a);

	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV>, "");
#else
		ARV arv{r};
#endif
		VERIFY(!arv.empty());
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.size() == 4);
		VERIFY(arv.reserve_hint() == 4);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV const>, "");
#else
		ARV const arv{r};
#endif
		VERIFY(!arv.empty());
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.size() == 4);
		VERIFY(arv.reserve_hint() == 4);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using R = test_input_view<int>;
	using ARV = hamon::ranges::as_rvalue_view<R>;

	static_assert( has_begin<ARV&>::value, "");
	static_assert( has_end<ARV&>::value, "");
	static_assert(!has_empty<ARV&>::value, "");
	static_assert( has_cbegin<ARV&>::value, "");
	static_assert( has_cend<ARV&>::value, "");
	static_assert(!has_operator_bool<ARV&>::value, "");
	static_assert(!has_data<ARV&>::value, "");
	static_assert(!has_size<ARV&>::value, "");
	static_assert(!has_reserve_hint<ARV&>::value, "");
	static_assert(!has_front<ARV&>::value, "");
	static_assert(!has_back<ARV&>::value, "");
	static_assert(!has_subscript<ARV&>::value, "");
	static_assert( has_base<ARV&>::value, "");

	static_assert( has_begin<ARV const&>::value, "");
	static_assert( has_end<ARV const&>::value, "");
	static_assert(!has_empty<ARV const&>::value, "");
	static_assert( has_cbegin<ARV const&>::value, "");
	static_assert( has_cend<ARV const&>::value, "");
	static_assert(!has_operator_bool<ARV const&>::value, "");
	static_assert(!has_data<ARV const&>::value, "");
	static_assert(!has_size<ARV const&>::value, "");
	static_assert(!has_reserve_hint<ARV const&>::value, "");
	static_assert(!has_front<ARV const&>::value, "");
	static_assert(!has_back<ARV const&>::value, "");
	static_assert(!has_subscript<ARV const&>::value, "");
	static_assert( has_base<ARV const&>::value, "");

	int a[2] = {1, 2};
	R r(a);

	auto rv1 = r | hamon::views::as_rvalue;
	static_assert(hamon::same_as<decltype(rv1), ARV>, "");

	auto rv2 = r | hamon::views::as_rvalue | hamon::views::as_rvalue;
	static_assert(hamon::same_as<decltype(rv2), ARV>, "");

	auto rv3 = r | (hamon::views::as_rvalue | hamon::views::as_rvalue);
	static_assert(hamon::same_as<decltype(rv3), ARV>, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using R = test_input_approximately_sized_view<int>;
	using ARV = hamon::ranges::as_rvalue_view<R>;

	static_assert( has_begin<ARV&>::value, "");
	static_assert( has_end<ARV&>::value, "");
	static_assert(!has_empty<ARV&>::value, "");
	static_assert( has_cbegin<ARV&>::value, "");
	static_assert( has_cend<ARV&>::value, "");
	static_assert(!has_operator_bool<ARV&>::value, "");
	static_assert(!has_data<ARV&>::value, "");
	static_assert(!has_size<ARV&>::value, "");
	static_assert( has_reserve_hint<ARV&>::value, "");
	static_assert(!has_front<ARV&>::value, "");
	static_assert(!has_back<ARV&>::value, "");
	static_assert(!has_subscript<ARV&>::value, "");
	static_assert( has_base<ARV&>::value, "");

	static_assert( has_begin<ARV const&>::value, "");
	static_assert( has_end<ARV const&>::value, "");
	static_assert(!has_empty<ARV const&>::value, "");
	static_assert( has_cbegin<ARV const&>::value, "");
	static_assert( has_cend<ARV const&>::value, "");
	static_assert(!has_operator_bool<ARV const&>::value, "");
	static_assert(!has_data<ARV const&>::value, "");
	static_assert(!has_size<ARV const&>::value, "");
	static_assert( has_reserve_hint<ARV const&>::value, "");
	static_assert(!has_front<ARV const&>::value, "");
	static_assert(!has_back<ARV const&>::value, "");
	static_assert(!has_subscript<ARV const&>::value, "");
	static_assert( has_base<ARV const&>::value, "");

	int a[] = {1, 2, 3, 4};
	R r(a);

	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV>, "");
#else
		ARV arv{r};
#endif
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.reserve_hint() == 4);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const arv{r};
		static_assert(hamon::same_as<decltype(arv), ARV const>, "");
#else
		ARV const arv{r};
#endif
		VERIFY(arv.base().begin() == r.begin());
		VERIFY(hamon::move(arv).base().begin() == r.begin());
		VERIFY(*arv.begin() == *r.begin());
		VERIFY(arv.end() != arv.begin());
		VERIFY(arv.reserve_hint() == 4);
	}

	return true;
}

// LWG 4083
struct I
{
	int operator*();
	using difference_type = int;
	I& operator++();
	void operator++(int);
};

HAMON_CXX14_CONSTEXPR bool test06()
{
	//hamon::ranges::range auto r =
	//	hamon::ranges::subrange{ I{}, hamon::unreachable_sentinel }
	//	| hamon::views::as_rvalue;
	//(void)r;

	auto r = hamon::ranges::make_subrange(I{}, hamon::unreachable_sentinel);
	static_assert(!hamon::invocable<decltype(hamon::views::as_rvalue), decltype(r)>, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsRvalueViewTest)
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

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NotSimpleViewCommonRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<ConstNotView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NonCopyableView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<ThrowOnCopyView>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<ThrowOnMoveView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace as_rvalue_view_test
}	// namespace hamon_ranges_test
