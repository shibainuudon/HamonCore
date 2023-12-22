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
static_assert(hamon::ranges::view_t<MoveOnlyView<int>>::value, "");
static_assert(!hamon::copyable_t<MoveOnlyView<int>>::value, "");

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
	constexpr std::size_t size() const { return m_last - m_first; }
};
static_assert( hamon::ranges::random_access_range_t<SizedViewWithUnsizedSentinel<int>>::value, "");
static_assert( hamon::ranges::sized_range_t<SizedViewWithUnsizedSentinel<int>>::value, "");
static_assert(!hamon::sized_sentinel_for_t<SizedViewWithUnsizedSentinel<int>::sentinel, SizedViewWithUnsizedSentinel<int>::iterator>::value, "");
static_assert( hamon::ranges::view_t<SizedViewWithUnsizedSentinel<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using RV = hamon::ranges::drop_view<V>;

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == hamon::ranges::borrowed_range_t<V>::value, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == hamon::ranges::contiguous_range_t<V>::value, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");
	
	static_assert(hamon::is_default_constructible<RV>::value == hamon::is_default_constructible<V>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value == hamon::is_nothrow_default_constructible<V>::value, "");

	static_assert(!hamon::is_constructible<RV, V>::value, "");
	static_assert( hamon::is_constructible<RV, V, hamon::ptrdiff_t>::value, "");
	static_assert(!hamon::is_constructible<RV, V, int*>::value, "");
	static_assert(!hamon::is_constructible<RV, V, hamon::ptrdiff_t, int>::value, "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(has_begin<RV>::value, "");
	static_assert(has_begin<RV const>::value ==
		(hamon::ranges::random_access_range_t<V const>::value && hamon::ranges::sized_range_t<V const>::value), "");

	static_assert(hamon::same_as_t<
		decltype(hamon::declval<RV>().begin()),
		decltype(hamon::ranges::begin(hamon::declval<V&>()))>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_begin<RV const>::value)
	{
		static_assert(hamon::same_as_t<
			decltype(hamon::declval<RV const>().begin()),
			decltype(hamon::ranges::begin(hamon::declval<V const&>()))>::value, "");
	}
#endif

	static_assert(has_end<RV>::value, "");
	static_assert(has_end<RV const>::value == hamon::ranges::range_t<V const>::value, "");

	static_assert(hamon::same_as_t<
		decltype(hamon::declval<RV>().end()),
		decltype(hamon::ranges::end(hamon::declval<V&>()))>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_end<RV const>::value)
	{
		static_assert(hamon::same_as_t<
			decltype(hamon::declval<RV const>().end()),
			decltype(hamon::ranges::end(hamon::declval<V const&>()))>::value, "");
	}
#endif

	static_assert(has_size<RV>::value == hamon::ranges::sized_range_t<V>::value, "");
	static_assert(has_size<RV const>::value == hamon::ranges::sized_range_t<V const>::value, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_size<RV>::value)
	{
		static_assert(hamon::same_as_t<
			decltype(hamon::declval<RV>().size()),
			decltype(hamon::ranges::size(hamon::declval<V&>()))>::value, "");
	}

	if constexpr (has_size<RV const>::value)
	{
		static_assert(hamon::same_as_t<
			decltype(hamon::declval<RV const>().size()),
			decltype(hamon::ranges::size(hamon::declval<V const&>()))>::value, "");
	}
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5};
	using R = test_random_access_view<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view rv{r, 3};
#else
	hamon::ranges::drop_view<R> rv{r, 3};
#endif
	auto const& crv = rv;

	VERIFY(rv.size() == 2);
	VERIFY(crv.size() == 2);

	static_assert( hamon::same_as_t<decltype(rv.begin()), decltype(r.begin())>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   decltype(r.begin())>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), decltype(cr.begin())>::value, "");
	static_assert(!hamon::same_as_t<decltype(crv.end()),   decltype(cr.begin())>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it == crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it == crv.end());
	}

	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5};
	using R = NotSimpleRandomAccessSizedView<int>;
	R r(a);
	auto const& cr = r;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view rv{r, 2};
#else
	hamon::ranges::drop_view<R> rv{r, 2};
#endif
	auto const& crv = rv;

	VERIFY(rv.size() == 3);
	VERIFY(crv.size() == 3);

	static_assert( hamon::same_as_t<decltype(rv.begin()), decltype(r.begin())>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   decltype(r.begin())>::value, "");
	static_assert( hamon::same_as_t<decltype(crv.begin()), decltype(cr.begin())>::value, "");
	static_assert(!hamon::same_as_t<decltype(crv.end()),   decltype(cr.begin())>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
	}
	{
		auto it = crv.begin();
		VERIFY(it == crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it != crv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != crv.begin());
		VERIFY(it == crv.end());
	}

	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5};
	using R = test_forward_view<int>;
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_view rv{r, 3};
#else
	hamon::ranges::drop_view<R> rv{r, 3};
#endif

	static_assert( hamon::same_as_t<decltype(rv.begin()), decltype(r.begin())>::value, "");
	static_assert(!hamon::same_as_t<decltype(rv.end()),   decltype(r.begin())>::value, "");

	{
		auto it = rv.begin();
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
	}

	VERIFY(rv.base().begin() == r.begin());
	VERIFY(hamon::move(rv).base().begin() == r.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// empty_view
	{
		auto rv = hamon::ranges::empty_view<int>{} | hamon::views::drop(2);
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::empty_view<int>>::value, "");
		VERIFY(rv.size() == 0);
	}

	// span
	{
		int a[] = {1,2,3,4,5};
		hamon::span<int> s(a);
		auto rv = s | hamon::views::drop(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::span<int>>::value, "");
		VERIFY(rv.size() == 2);
	}
	{
		int a[] = {1,2,3,4,5,6,7,8};
		hamon::span<int, 8> s(a);
		auto rv = s | hamon::views::drop(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::span<int, hamon::dynamic_extent>>::value, "");
		VERIFY(rv.size() == 5);
	}

	// string_view
	{
		hamon::string_view sv = "abcdefg";
		auto rv = sv | hamon::views::drop(4);
		static_assert( hamon::same_as_t<decltype(rv), hamon::string_view>::value, "");
		VERIFY(rv.size() == 3);
	}

	// iota_view
	{
		auto rv = hamon::views::iota(1, 8) | hamon::views::drop(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::iota_view<int, int>>::value, "");
		VERIFY(rv.size() == 4);
		VERIFY(*rv.begin() == 4);
	}
	{
		auto rv = hamon::views::iota(1) | hamon::views::drop(3);
		static_assert( hamon::same_as_t<decltype(rv),
			hamon::ranges::drop_view<hamon::ranges::iota_view<int, hamon::unreachable_sentinel_t>>>::value, "");
		static_assert(!has_size<decltype(rv)>::value, "");
		VERIFY(*rv.begin() == 4);
	}

	// subrange
	{
		int a[] = {1,2,3,4,5,6,7,8};
		hamon::ranges::subrange<int*> s(a, a + 5);
		auto rv = s | hamon::views::drop(2);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::subrange<int*>>::value, "");
		VERIFY(rv.size() == 3);
	}
	{
		int a[] = {1,2,3,4,5,6,7,8};
		using R = SizedViewWithUnsizedSentinel<int>;
		using I = hamon::ranges::iterator_t<R>;
		using S = hamon::ranges::sentinel_t<R>;
		R r(a);
		hamon::ranges::subrange<I, S, hamon::ranges::subrange_kind::sized> s(r.begin(), r.end(), 8);
		auto rv = s | hamon::views::drop(2);
		static_assert( hamon::same_as_t<decltype(rv), decltype(s)>::value, "");
		VERIFY(rv.size() == 6);
	}

	// repeat_view
	{
		auto rv = hamon::views::repeat(42, 8) | hamon::views::drop(3);
		static_assert( hamon::same_as_t<decltype(rv), hamon::ranges::repeat_view<int, int>>::value, "");
		VERIFY(rv.size() == 5);
		VERIFY(*rv.begin() == 42);
	}
	{
		auto rv = hamon::views::repeat(42) | hamon::views::drop(3);
		static_assert( hamon::same_as_t<decltype(rv), decltype(hamon::views::repeat(42))>::value, "");
		static_assert(!has_size<decltype(rv)>::value, "");
		VERIFY(*rv.begin() == 42);
	}

	{
		int a[] = {1,2,3,4,5};
		auto rv = a | hamon::views::drop(2);
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::drop_view<hamon::ranges::ref_view<int[5]>>>::value, "");
		VERIFY(rv.size() == 3);
	}
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
