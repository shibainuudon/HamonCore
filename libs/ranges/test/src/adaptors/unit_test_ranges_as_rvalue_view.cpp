/**
 *	@file	unit_test_ranges_as_rvalue_view.cpp
 *
 *	@brief	ranges::as_rvalue_view のテスト
 */

#include <hamon/ranges/adaptors/as_rvalue_view.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
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

static_assert(hamon::ranges::view_t<NotSimpleView<int>>::value, "");
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

static_assert(hamon::ranges::view_t<NotSimpleViewCommonRange<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<NotSimpleViewCommonRange<int>>::value, "");
static_assert(hamon::ranges::range_t<NotSimpleViewCommonRange<int>>::value, "");
static_assert(hamon::ranges::common_range_t<NotSimpleViewCommonRange<int>>::value, "");

template <typename T>
struct ConstNotView : hamon::ranges::view_base
{
	using iterator = T*;
	using sentinel = T*;

	HAMON_CXX14_CONSTEXPR iterator begin() noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR sentinel end()   noexcept { return nullptr; }
};

static_assert(hamon::ranges::view_t<ConstNotView<int>>::value, "");
static_assert(!hamon::ranges::detail::simple_view_t<ConstNotView<int>>::value, "");
static_assert( hamon::ranges::range_t<ConstNotView<int>>::value, "");
static_assert(!hamon::ranges::range_t<ConstNotView<int> const>::value, "");

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

static_assert(hamon::ranges::view_t<NonCopyableView<int>>::value, "");
static_assert(hamon::ranges::detail::simple_view_t<NonCopyableView<int>>::value, "");
static_assert(!hamon::copy_constructible_t<NonCopyableView<int>>::value, "");

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

static_assert(hamon::ranges::view_t<ThrowOnCopyView<int>>::value, "");
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

static_assert(hamon::ranges::view_t<ThrowOnMoveView<int>>::value, "");
static_assert(hamon::ranges::detail::simple_view_t<ThrowOnMoveView<int>>::value, "");
static_assert(hamon::is_move_constructible<ThrowOnMoveView<int>>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<ThrowOnMoveView<int>>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<ThrowOnMoveView<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using RV = hamon::ranges::as_rvalue_view<V>;

	static_assert(hamon::is_default_constructible<RV>::value == hamon::is_default_constructible<V>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value == hamon::is_nothrow_default_constructible<V>::value, "");

	static_assert(hamon::is_constructible<RV, V>::value, "");
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
	static_assert(hamon::is_nothrow_constructible<RV, V>::value == hamon::is_nothrow_move_constructible<V>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<RV, V>::value, "");

	static_assert(hamon::ranges::view_t<RV>::value, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == hamon::ranges::borrowed_range_t<V>::value, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(!hamon::ranges::output_range_t<RV, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(!hamon::ranges::contiguous_range_t<RV>::value, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value, "");
	static_assert(hamon::ranges::view_t<RV>::value, "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().base()), V>::value, "");
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
	static_assert(noexcept(hamon::declval<RV&&>().base()) == hamon::is_nothrow_move_constructible<V>::value, "");
#endif

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible_t<V>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().base()), V>::value, "");
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
		static_assert(noexcept(hamon::declval<RV&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
#endif
	}
#endif

	{
		using I = decltype(hamon::ranges::begin(hamon::declval<V&>()));

		static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().begin()), hamon::move_iterator<I>>::value, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (hamon::ranges::common_range_t<V>::value)
		{
			static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().end()), hamon::move_iterator<I>>::value, "");
		}
		else
		{
			using S = decltype(hamon::ranges::end(hamon::declval<V&>()));
			static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().end()), hamon::move_sentinel<S>>::value, "");
		}
#endif

#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
		static_assert(noexcept(hamon::declval<RV&>().begin()) == noexcept(hamon::ranges::begin(hamon::declval<V&>())), "");
		static_assert(noexcept(hamon::declval<RV&>().end()) == noexcept(hamon::ranges::end(hamon::declval<V&>())), "");
#endif
	}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::ranges::range_t<V const>::value)
	{
		using CI = decltype(hamon::ranges::begin(hamon::declval<V const&>()));
		using CS = decltype(hamon::ranges::end(hamon::declval<V const&>()));

		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().begin()), hamon::move_iterator<CI>>::value, "");

		if constexpr (hamon::ranges::common_range_t<V const>::value)
		{
			static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().end()), hamon::move_iterator<CI>>::value, "");
		}
		else
		{
			static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().end()), hamon::move_sentinel<CS>>::value, "");
		}

#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
		static_assert(noexcept(hamon::declval<RV const&>().begin()), "");
		static_assert(noexcept(hamon::declval<RV const&>().end()), "");
#endif
	}
#endif

	static_assert(has_begin<RV>::value, "");
	static_assert(has_begin<RV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(has_end<RV>::value, "");
	static_assert(has_end<RV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(has_size<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(has_size<RV const>::value == hamon::ranges::sized_range_t<V const>::value, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
#if !defined(HAMON_USE_STD_RANGES_AS_RVALUE_VIEW)
	if constexpr (has_size<RV>::value)
	{
		static_assert(noexcept(hamon::declval<RV&>().size()) == noexcept(hamon::ranges::size(hamon::declval<V&>())), "");
	}

	if constexpr (has_size<RV const>::value)
	{
		static_assert(noexcept(hamon::declval<RV const&>().size()) == noexcept(hamon::ranges::size(hamon::declval<V const&>())), "");
	}
#endif
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] = {1, 2};
	using R = test_random_access_view<int>;
	R r(a);

	{
		hamon::ranges::as_rvalue_view<R> rv{};
		VERIFY(rv.empty());
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view rv{r};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::as_rvalue_view<R>>::value, "");
#else
		hamon::ranges::as_rvalue_view<R> rv{r};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());
		VERIFY(*rv.begin() == *r.begin());
		VERIFY(rv.end() != rv.begin());
		VERIFY(rv.size() == 2);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const rv{r};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::as_rvalue_view<R> const>::value, "");
#else
		hamon::ranges::as_rvalue_view<R> const rv{r};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());
		VERIFY(*rv.begin() == *r.begin());
		VERIFY(rv.end() != rv.begin());
		VERIFY(rv.size() == 2);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3};
	using R = NotSimpleView<int>;
	R r(a);

	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view rv{r};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::as_rvalue_view<R>>::value, "");
#else
		hamon::ranges::as_rvalue_view<R> rv{r};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());
		VERIFY(*rv.begin() == *r.begin());
		VERIFY(rv.end() != rv.begin());
		VERIFY(rv.size() == 3);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const rv{r};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::as_rvalue_view<R> const>::value, "");
#else
		hamon::ranges::as_rvalue_view<R> const rv{r};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());
		VERIFY(*rv.begin() == *r.begin());
		VERIFY(rv.end() != rv.begin());
		VERIFY(rv.size() == 3);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4};
	using R = NotSimpleViewCommonRange<int>;
	R r(a);

	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view rv{r};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::as_rvalue_view<R>>::value, "");
#else
		hamon::ranges::as_rvalue_view<R> rv{r};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());
		VERIFY(*rv.begin() == *r.begin());
		VERIFY(rv.end() != rv.begin());
		VERIFY(rv.size() == 4);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::as_rvalue_view const rv{r};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::as_rvalue_view<R> const>::value, "");
#else
		hamon::ranges::as_rvalue_view<R> const rv{r};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());
		VERIFY(*rv.begin() == *r.begin());
		VERIFY(rv.end() != rv.begin());
		VERIFY(rv.size() == 4);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[2] = {1, 2};
	using R = test_input_view<int>;
	R r(a);

	auto rv1 = r | hamon::views::as_rvalue;
	static_assert(hamon::same_as_t<decltype(rv1), hamon::ranges::as_rvalue_view<R>>::value, "");

	auto rv2 = r | hamon::views::as_rvalue | hamon::views::as_rvalue;
	static_assert(hamon::same_as_t<decltype(rv2), hamon::ranges::as_rvalue_view<R>>::value, "");

	auto rv3 = r | (hamon::views::as_rvalue | hamon::views::as_rvalue);
	static_assert(hamon::same_as_t<decltype(rv3), hamon::ranges::as_rvalue_view<R>>::value, "");

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
}

}	// namespace as_rvalue_view_test
}	// namespace hamon_ranges_test
