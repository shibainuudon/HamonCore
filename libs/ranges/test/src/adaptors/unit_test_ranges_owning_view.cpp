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
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace owning_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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
	using OV = hamon::ranges::owning_view<RangeWrapper<T>>;

	static_assert(!hamon::constructible_from<OV, T>, "");
	static_assert(!hamon::constructible_from<OV, T&>, "");
	static_assert(!hamon::constructible_from<OV, T&&>, "");
	static_assert(!hamon::constructible_from<OV, T const>, "");
	static_assert(!hamon::constructible_from<OV, T const&>, "");
	static_assert(!hamon::constructible_from<OV, T const&&>, "");

	static_assert( hamon::constructible_from<OV, R>, "");
	static_assert(!hamon::constructible_from<OV, R&>, "");
	static_assert( hamon::constructible_from<OV, R&&>, "");
	static_assert(!hamon::constructible_from<OV, R const>, "");
	static_assert(!hamon::constructible_from<OV, R const&>, "");
	static_assert(!hamon::constructible_from<OV, R const&&>, "");

	static_assert( hamon::constructible_from<OV, OV>, "");
	static_assert(!hamon::constructible_from<OV, OV&>, "");
	static_assert( hamon::constructible_from<OV, OV&&>, "");
	static_assert(!hamon::constructible_from<OV, OV const>, "");
	static_assert(!hamon::constructible_from<OV, OV const&>, "");
	static_assert(!hamon::constructible_from<OV, OV const&&>, "");

	static_assert( hamon::ranges::range_t<OV>::value, "");
	static_assert( hamon::ranges::borrowed_range<OV> == hamon::ranges::borrowed_range<R>, "");
	static_assert( hamon::ranges::sized_range_t<OV>::value == hamon::ranges::sized_range_t<R>::value, "");
	static_assert( hamon::ranges::approximately_sized_range<OV> == hamon::ranges::approximately_sized_range<R>, "");
	static_assert( hamon::ranges::output_range<OV, T> == hamon::ranges::output_range<R, T>, "");
	static_assert( hamon::ranges::input_range<OV> == hamon::ranges::input_range<R>, "");
	static_assert( hamon::ranges::forward_range<OV> == hamon::ranges::forward_range<R>, "");
	static_assert( hamon::ranges::bidirectional_range<OV> == hamon::ranges::bidirectional_range<R>, "");
	static_assert( hamon::ranges::random_access_range_t<OV>::value == hamon::ranges::random_access_range_t<R>::value, "");
	static_assert( hamon::ranges::contiguous_range<OV> == hamon::ranges::contiguous_range<R>, "");
	static_assert( hamon::ranges::common_range<OV> == hamon::ranges::common_range<R>, "");
	static_assert( hamon::ranges::viewable_range_t<OV>::value, "");
	static_assert( hamon::ranges::view_t<OV>::value, "");
	static_assert(!hamon::ranges::constant_range<OV>, "");

	static_assert(hamon::is_default_constructible<OV>::value == hamon::is_default_constructible<R>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<OV>::value == hamon::is_nothrow_default_constructible<R>::value, "");

	static_assert(hamon::is_nothrow_move_constructible<OV>::value == hamon::is_nothrow_move_constructible<R>::value, "");
	static_assert(hamon::is_nothrow_move_assignable<OV>::value == hamon::is_nothrow_move_assignable<R>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
	static_assert(hamon::is_nothrow_constructible<OV, R&&>::value == hamon::is_nothrow_move_constructible<R>::value, "");
	static_assert(noexcept(hamon::declval<OV&>().begin()), "");
	static_assert(noexcept(hamon::declval<OV const&>().begin()), "");
	static_assert(noexcept(hamon::declval<OV&>().end()), "");
	static_assert(noexcept(hamon::declval<OV const&>().end()), "");
#endif

	static_assert(hamon::same_as<decltype(hamon::declval<OV&>().base()),  R&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<OV&&>().base()), R&&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<OV const&>().base()),  const R&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<OV const&&>().base()), const R&&>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<OV&>().begin()), hamon::ranges::iterator_t<R>>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<OV const&>().begin()), hamon::ranges::iterator_t<R>>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<OV&>().end()), hamon::ranges::sentinel_t<R>>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<OV const&>().end()), hamon::ranges::sentinel_t<R>>, "");

	static_assert(noexcept(hamon::declval<OV&>().base()), "");
	static_assert(noexcept(hamon::declval<OV&&>().base()), "");
	static_assert(noexcept(hamon::declval<OV const&>().base()), "");
	static_assert(noexcept(hamon::declval<OV const&&>().base()), "");

	static_assert(has_empty<OV&>::value ==
		(hamon::ranges::sized_range_t<R>::value || hamon::ranges::forward_range<R>), "");
	static_assert(has_empty<OV const&>::value ==
		(hamon::ranges::sized_range_t<R>::value || hamon::ranges::forward_range<R>), "");

	static_assert(has_size<OV&>::value == hamon::ranges::sized_range_t<R>::value, "");
	static_assert(has_size<OV const&>::value == hamon::ranges::sized_range_t<R>::value, "");
	
	static_assert(has_reserve_hint<OV&>::value == hamon::ranges::approximately_sized_range<R>, "");
	static_assert(has_reserve_hint<OV const&>::value == hamon::ranges::approximately_sized_range<R>, "");

	static_assert(has_data<OV&>::value == hamon::ranges::contiguous_range<R>, "");
	static_assert(has_data<OV const&>::value == hamon::ranges::contiguous_range<R>, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] = {1, 2};
	test_random_access_range<int> r(a);
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view ov{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_random_access_range<int>> ov{hamon::move(r)};
#endif

		using OV = decltype(ov);

		static_assert( has_begin<OV>::value, "");
		static_assert( has_end<OV>::value, "");
		static_assert( has_empty<OV>::value, "");
		static_assert( has_cbegin<OV>::value, "");
		static_assert( has_cend<OV>::value, "");
		static_assert( has_operator_bool<OV>::value, "");
		static_assert(!has_data<OV>::value, "");
		static_assert( has_size<OV>::value, "");
		static_assert( has_reserve_hint<OV>::value, "");
		static_assert( has_front<OV>::value, "");
		static_assert(!has_back<OV>::value, "");
		static_assert( has_subscript<OV>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(ov.empty()), "");
		static_assert(noexcept(ov.size()), "");
		static_assert(noexcept(ov.reserve_hint()), "");
#endif

		VERIFY(&ov.base() != &r);
		VERIFY(!ov.empty());
		VERIFY(ov.size() == 2);
		VERIFY(ov.reserve_hint() == 2);
		VERIFY(ov.begin() == r.begin());
		VERIFY(ov.cbegin() == r.begin());
		VERIFY(ov.end().m_it == r.end().m_it);
		VERIFY(ov.cend().m_it == r.end().m_it);
		VERIFY(ov.front() == 1);
		VERIFY(ov[1] == 2);

		auto rr = hamon::move(ov).base();
		VERIFY(&rr != &r);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view const ov{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_random_access_range<int>> const ov{hamon::move(r)};
#endif

		using OV = decltype(ov);
		static_assert( has_begin<OV>::value, "");
		static_assert( has_end<OV>::value, "");
		static_assert( has_empty<OV>::value, "");
		static_assert( has_cbegin<OV>::value, "");
		static_assert( has_cend<OV>::value, "");
		static_assert( has_operator_bool<OV>::value, "");
		static_assert(!has_data<OV>::value, "");
		static_assert( has_size<OV>::value, "");
		static_assert( has_reserve_hint<OV>::value, "");
		static_assert( has_front<OV>::value, "");
		static_assert(!has_back<OV>::value, "");
		static_assert( has_subscript<OV>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(ov.empty()), "");
		static_assert(noexcept(ov.size()), "");
		static_assert(noexcept(ov.reserve_hint()), "");
#endif

		VERIFY(&ov.base() != &r);
		VERIFY(!ov.empty());
		VERIFY(ov.size() == 2);
		VERIFY(ov.reserve_hint() == 2);
		VERIFY(ov.begin() == r.begin());
		VERIFY(ov.cbegin() == r.begin());
		VERIFY(ov.end().m_it == r.end().m_it);
		VERIFY(ov.cend().m_it == r.end().m_it);
		VERIFY(ov.front() == 1);
		VERIFY(ov[1] == 2);

		auto rr = hamon::move(ov).base();
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
		hamon::ranges::owning_view ov{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_contiguous_range<int>> ov{hamon::move(r)};
#endif

		using OV = decltype(ov);
		static_assert( has_begin<OV>::value, "");
		static_assert( has_end<OV>::value, "");
		static_assert( has_empty<OV>::value, "");
		static_assert( has_cbegin<OV>::value, "");
		static_assert( has_cend<OV>::value, "");
		static_assert( has_operator_bool<OV>::value, "");
		static_assert( has_data<OV>::value, "");
		static_assert( has_size<OV>::value, "");
		static_assert( has_reserve_hint<OV>::value, "");
		static_assert( has_front<OV>::value, "");
		static_assert(!has_back<OV>::value, "");
		static_assert( has_subscript<OV>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(ov.empty()), "");
		static_assert(noexcept(ov.size()), "");
		static_assert(noexcept(ov.reserve_hint()), "");
		static_assert(noexcept(ov.data()), "");
#endif

		VERIFY(&ov.base() != &r);
		VERIFY(!ov.empty());
		VERIFY(ov.size() == 3);
		VERIFY(ov.reserve_hint() == 3);
		VERIFY(ov.begin() == r.begin());
		VERIFY(ov.end().m_it == r.end().m_it);
		VERIFY(ov.data() == a);
		VERIFY(ov.cbegin() == r.begin());
		VERIFY(ov.cend().m_it == r.end().m_it);
		VERIFY(ov.front() == 3);
		VERIFY(ov[1] == 4);

		auto rr = hamon::move(ov).base();
		VERIFY(&rr != &r);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view const ov{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_contiguous_range<int>> const ov{hamon::move(r)};
#endif

		using OV = decltype(ov);
		static_assert( has_begin<OV>::value, "");
		static_assert( has_end<OV>::value, "");
		static_assert( has_empty<OV>::value, "");
		static_assert( has_cbegin<OV>::value, "");
		static_assert( has_cend<OV>::value, "");
		static_assert( has_operator_bool<OV>::value, "");
		static_assert( has_data<OV>::value, "");
		static_assert( has_size<OV>::value, "");
		static_assert( has_reserve_hint<OV>::value, "");
		static_assert( has_front<OV>::value, "");
		static_assert(!has_back<OV>::value, "");
		static_assert( has_subscript<OV>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(ov.empty()), "");
		static_assert(noexcept(ov.size()), "");
		static_assert(noexcept(ov.reserve_hint()), "");
		static_assert(noexcept(ov.data()), "");
#endif

		VERIFY(&ov.base() != &r);
		VERIFY(!ov.empty());
		VERIFY(ov.size() == 3);
		VERIFY(ov.reserve_hint() == 3);
		VERIFY(ov.begin() == r.begin());
		VERIFY(ov.end().m_it == r.end().m_it);
		VERIFY(ov.data() == a);
		VERIFY(ov.cbegin() == r.begin());
		VERIFY(ov.cend().m_it == r.end().m_it);
		VERIFY(ov.front() == 3);
		VERIFY(ov[1] == 4);

		auto rr = hamon::move(ov).base();
		VERIFY(&rr != &r);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[3] = {3, 4, 5};
	test_input_approximately_sized_range<int> r(a);
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view ov{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_input_approximately_sized_range<int>> ov{hamon::move(r)};
#endif

		using OV = decltype(ov);
		static_assert( has_begin<OV>::value, "");
		static_assert( has_end<OV>::value, "");
		static_assert(!has_empty<OV>::value, "");
		static_assert( has_cbegin<OV>::value, "");
		static_assert( has_cend<OV>::value, "");
		static_assert(!has_operator_bool<OV>::value, "");
		static_assert(!has_data<OV>::value, "");
		static_assert(!has_size<OV>::value, "");
		static_assert( has_reserve_hint<OV>::value, "");
		static_assert(!has_front<OV>::value, "");
		static_assert(!has_back<OV>::value, "");
		static_assert(!has_subscript<OV>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(ov.reserve_hint()), "");
#endif
		VERIFY(&ov.base() != &r);
		VERIFY(ov.reserve_hint() == 3);
		VERIFY(ov.begin() == r.begin());
		VERIFY(ov.end().m_it == r.end().m_it);
		VERIFY(ov.cbegin() == r.begin());
		VERIFY(ov.cend().m_it == r.end().m_it);

		auto rr = hamon::move(ov).base();
		VERIFY(&rr != &r);
	}
	{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::owning_view const ov{hamon::move(r)};
#else
		hamon::ranges::owning_view<test_input_approximately_sized_range<int>> const ov{hamon::move(r)};
#endif

		using OV = decltype(ov);
		static_assert( has_begin<OV>::value, "");
		static_assert( has_end<OV>::value, "");
		static_assert(!has_empty<OV>::value, "");
		static_assert( has_cbegin<OV>::value, "");
		static_assert( has_cend<OV>::value, "");
		static_assert(!has_operator_bool<OV>::value, "");
		static_assert(!has_data<OV>::value, "");
		static_assert(!has_size<OV>::value, "");
		static_assert( has_reserve_hint<OV>::value, "");
		static_assert(!has_front<OV>::value, "");
		static_assert(!has_back<OV>::value, "");
		static_assert(!has_subscript<OV>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(ov.reserve_hint()), "");
#endif

		VERIFY(&ov.base() != &r);
		VERIFY(ov.reserve_hint() == 3);
		VERIFY(ov.begin() == r.begin());
		VERIFY(ov.end().m_it == r.end().m_it);
		VERIFY(ov.cbegin() == r.begin());
		VERIFY(ov.cend().m_it == r.end().m_it);

		auto rr = hamon::move(ov).base();
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

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_approximately_sized_range>());

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
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace owning_view_test
}	// namespace hamon_ranges_test
