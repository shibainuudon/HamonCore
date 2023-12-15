/**
 *	@file	unit_test_ranges_owning_view.cpp
 *
 *	@brief	ranges::owning_view のテスト
 */

#include <hamon/ranges/adaptors/owning_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace owning_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename = void>
struct has_empty
	: public hamon::false_type {};

template <typename T>
struct has_empty<T, hamon::void_t<decltype(hamon::declval<T>().empty())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_data
	: public hamon::false_type {};

template <typename T>
struct has_data<T, hamon::void_t<decltype(hamon::declval<T>().data())>>
	: public hamon::true_type {};

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct NoDefaultCtorRange : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	NoDefaultCtorRange() = delete;
};
template <typename T> using NoDefaultCtorContiguousRange    = NoDefaultCtorRange<T, contiguous_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorRandomAccessRange  = NoDefaultCtorRange<T, random_access_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorBidirectionalRange = NoDefaultCtorRange<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorForwardRange       = NoDefaultCtorRange<T, forward_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorInputRange         = NoDefaultCtorRange<T, input_iterator_wrapper<T>>;
template <typename T> using NoDefaultCtorOutputRange        = NoDefaultCtorRange<T, output_iterator_wrapper<T>>;

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct NoThrowDefaultCtorRange : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	NoThrowDefaultCtorRange() noexcept {}
};
template <typename T> using NoThrowDefaultCtorContiguousRange    = NoThrowDefaultCtorRange<T, contiguous_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorRandomAccessRange  = NoThrowDefaultCtorRange<T, random_access_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorBidirectionalRange = NoThrowDefaultCtorRange<T, bidirectional_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorForwardRange       = NoThrowDefaultCtorRange<T, forward_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorInputRange         = NoThrowDefaultCtorRange<T, input_iterator_wrapper<T>>;
template <typename T> using NoThrowDefaultCtorOutputRange        = NoThrowDefaultCtorRange<T, output_iterator_wrapper<T>>;

template <template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using R = RangeWrapper<T>;
	using RV = hamon::ranges::owning_view<RangeWrapper<T>>;

	static_assert(!hamon::constructible_from_t<RV, T>::value, "");
	static_assert(!hamon::constructible_from_t<RV, T&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, T&&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, T const>::value, "");
	static_assert(!hamon::constructible_from_t<RV, T const&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, T const&&>::value, "");

	static_assert( hamon::constructible_from_t<RV, R>::value, "");
	static_assert(!hamon::constructible_from_t<RV, R&>::value, "");
	static_assert( hamon::constructible_from_t<RV, R&&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, R const>::value, "");
	static_assert(!hamon::constructible_from_t<RV, R const&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, R const&&>::value, "");

	static_assert( hamon::constructible_from_t<RV, RV>::value, "");
	static_assert(!hamon::constructible_from_t<RV, RV&>::value, "");
	static_assert( hamon::constructible_from_t<RV, RV&&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, RV const>::value, "");
	static_assert(!hamon::constructible_from_t<RV, RV const&>::value, "");
	static_assert(!hamon::constructible_from_t<RV, RV const&&>::value, "");

	static_assert(hamon::ranges::borrowed_range_t<RV>::value == hamon::ranges::borrowed_range_t<R>::value, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == hamon::ranges::sized_range_t<R>::value, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<R, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<R>::value, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<R>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<R>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<R>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == hamon::ranges::contiguous_range_t<R>::value, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == hamon::ranges::common_range_t<R>::value, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value, "");
	static_assert(hamon::ranges::view_t<RV>::value, "");

	static_assert(hamon::is_default_constructible<RV>::value == hamon::is_default_constructible<R>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value == hamon::is_nothrow_default_constructible<R>::value, "");

	static_assert(hamon::is_nothrow_move_constructible<RV>::value == hamon::is_nothrow_move_constructible<R>::value, "");
	static_assert(hamon::is_nothrow_move_assignable<RV>::value == hamon::is_nothrow_move_assignable<R>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
	static_assert(hamon::is_nothrow_constructible<RV, R&&>::value == hamon::is_nothrow_move_constructible<R>::value, "");
	static_assert(noexcept(hamon::declval<RV&>().begin()), "");
	static_assert(noexcept(hamon::declval<RV const&>().begin()), "");
	static_assert(noexcept(hamon::declval<RV&>().end()), "");
	static_assert(noexcept(hamon::declval<RV const&>().end()), "");
#endif

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().base()),  R&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().base()), R&&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().base()),  const R&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().base()), const R&&>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().begin()), hamon::ranges::iterator_t<R>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().begin()), hamon::ranges::iterator_t<R>>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().end()), hamon::ranges::sentinel_t<R>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().end()), hamon::ranges::sentinel_t<R>>::value, "");

	static_assert(noexcept(hamon::declval<RV&>().base()), "");
	static_assert(noexcept(hamon::declval<RV&&>().base()), "");
	static_assert(noexcept(hamon::declval<RV const&>().base()), "");
	static_assert(noexcept(hamon::declval<RV const&&>().base()), "");

	static_assert(has_empty<RV&>::value ==
		(hamon::ranges::sized_range_t<R>::value || hamon::ranges::forward_range_t<R>::value), "");
	static_assert(has_empty<RV const&>::value ==
		(hamon::ranges::sized_range_t<R>::value || hamon::ranges::forward_range_t<R>::value), "");

	static_assert(has_size<RV&>::value == hamon::ranges::sized_range_t<R>::value, "");
	static_assert(has_size<RV const&>::value == hamon::ranges::sized_range_t<R>::value, "");
	
	static_assert(has_data<RV&>::value == hamon::ranges::contiguous_range_t<R>::value, "");
	static_assert(has_data<RV const&>::value == hamon::ranges::contiguous_range_t<R>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] = {1, 2};
	test_random_access_range<int> r(a);
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view rv{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_random_access_range<int>> rv{hamon::move(r)};
#endif

		VERIFY(&rv.base() != &r);
		VERIFY(!rv.empty());
		VERIFY(rv.size() == 2);
		VERIFY(rv.begin() == r.begin());
		VERIFY(rv.cbegin() == r.begin());
		VERIFY(rv.end().m_it == r.end().m_it);
		VERIFY(rv.cend().m_it == r.end().m_it);
		VERIFY(rv.front() == 1);
		VERIFY(rv[1] == 2);
#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(rv.empty()), "");
		static_assert(noexcept(rv.size()), "");
#endif
		auto rr = hamon::move(rv).base();
		VERIFY(&rr != &r);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view const rv{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_random_access_range<int>> const rv{hamon::move(r)};
#endif

		VERIFY(&rv.base() != &r);
		VERIFY(!rv.empty());
		VERIFY(rv.size() == 2);
		VERIFY(rv.begin() == r.begin());
		VERIFY(rv.cbegin() == r.begin());
		VERIFY(rv.end().m_it == r.end().m_it);
		VERIFY(rv.cend().m_it == r.end().m_it);
		VERIFY(rv.front() == 1);
		VERIFY(rv[1] == 2);
#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(rv.empty()), "");
		static_assert(noexcept(rv.size()), "");
#endif
		auto rr = hamon::move(rv).base();
		VERIFY(&rr != &r);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[3] = {3, 4, 5};
	test_contiguous_range<int> r(a);
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view rv{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_contiguous_range<int>> rv{hamon::move(r)};
#endif

		VERIFY(&rv.base() != &r);
		VERIFY(!rv.empty());
		VERIFY(rv.size() == 3);
		VERIFY(rv.begin() == r.begin());
		VERIFY(rv.end().m_it == r.end().m_it);
		VERIFY(rv.data() == a);
#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(rv.empty()), "");
		static_assert(noexcept(rv.size()), "");
		static_assert(noexcept(rv.data()), "");
#endif
		VERIFY(rv.cbegin() == r.begin());
		VERIFY(rv.cend().m_it == r.end().m_it);
		VERIFY(rv.front() == 3);
		VERIFY(rv[1] == 4);

		auto rr = hamon::move(rv).base();
		VERIFY(&rr != &r);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view const rv{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_contiguous_range<int>> const rv{hamon::move(r)};
#endif

		VERIFY(&rv.base() != &r);
		VERIFY(!rv.empty());
		VERIFY(rv.size() == 3);
		VERIFY(rv.begin() == r.begin());
		VERIFY(rv.end().m_it == r.end().m_it);
		VERIFY(rv.data() == a);
#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(rv.empty()), "");
		static_assert(noexcept(rv.size()), "");
		static_assert(noexcept(rv.data()), "");
#endif
		VERIFY(rv.cbegin() == r.begin());
		VERIFY(rv.cend().m_it == r.end().m_it);
		VERIFY(rv.front() == 3);
		VERIFY(rv[1] == 4);

		auto rr = hamon::move(rv).base();
		VERIFY(&rr != &r);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, OwningViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_output_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_range>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_common_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_output_borrowed_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_borrowed_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_borrowed_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_borrowed_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_borrowed_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_borrowed_range>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_output_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_sized_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoDefaultCtorOutputRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoDefaultCtorInputRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoDefaultCtorForwardRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoDefaultCtorBidirectionalRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoDefaultCtorRandomAccessRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoDefaultCtorContiguousRange>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoThrowDefaultCtorOutputRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoThrowDefaultCtorInputRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoThrowDefaultCtorForwardRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoThrowDefaultCtorBidirectionalRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoThrowDefaultCtorRandomAccessRange>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<NoThrowDefaultCtorContiguousRange>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace owning_view_test
}	// namespace hamon_ranges_test
