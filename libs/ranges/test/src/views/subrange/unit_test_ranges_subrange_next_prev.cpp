/**
 *	@file	unit_test_ranges_subrange_next_prev.cpp
 *
 *	@brief	ranges::subrange::next, prev のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace next_prev_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename S>
struct HasNextImpl
{
private:
	template <typename S2,
		typename = decltype(std::declval<S2>().next())
	>
	static auto test(int) -> std::true_type;

	template <typename S2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<S>(0));
};

template <typename S>
using HasNext = typename HasNextImpl<S>::type;

template <typename S>
struct HasPrevImpl
{
private:
	template <typename S2,
		typename = decltype(std::declval<S2>().prev())
	>
	static auto test(int) -> std::true_type;

	template <typename S2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<S>(0));
};

template <typename S>
using HasPrev = typename HasPrevImpl<S>::type;

using InputSubrange         = hamon::ranges::subrange<input_iterator_wrapper<int>>;
using ForwardSubrange       = hamon::ranges::subrange<forward_iterator_wrapper<int>>;
using BidirectionalSubrange = hamon::ranges::subrange<bidirectional_iterator_wrapper<int>>;
using RandomAccessSubrange  = hamon::ranges::subrange<random_access_iterator_wrapper<int>>;

static_assert( HasNext<InputSubrange>::value, "");
static_assert(!HasNext<InputSubrange &>::value, "");
static_assert(!HasNext<InputSubrange const&>::value, "");
static_assert( HasNext<InputSubrange &&>::value, "");
static_assert(!HasNext<InputSubrange const&&>::value, "");
static_assert( HasNext<ForwardSubrange>::value, "");
static_assert( HasNext<ForwardSubrange &>::value, "");
static_assert( HasNext<ForwardSubrange const&>::value, "");
static_assert( HasNext<ForwardSubrange &&>::value, "");
static_assert( HasNext<ForwardSubrange const&&>::value, "");
static_assert( HasNext<BidirectionalSubrange>::value, "");
static_assert( HasNext<BidirectionalSubrange &>::value, "");
static_assert( HasNext<BidirectionalSubrange const&>::value, "");
static_assert( HasNext<BidirectionalSubrange &&>::value, "");
static_assert( HasNext<BidirectionalSubrange const&&>::value, "");
static_assert( HasNext<RandomAccessSubrange>::value, "");
static_assert( HasNext<RandomAccessSubrange &>::value, "");
static_assert( HasNext<RandomAccessSubrange const&>::value, "");
static_assert( HasNext<RandomAccessSubrange &&>::value, "");
static_assert( HasNext<RandomAccessSubrange const&&>::value, "");

static_assert(!HasPrev<InputSubrange>::value, "");
static_assert(!HasPrev<InputSubrange &>::value, "");
static_assert(!HasPrev<InputSubrange const&>::value, "");
static_assert(!HasPrev<InputSubrange &&>::value, "");
static_assert(!HasPrev<InputSubrange const&&>::value, "");
static_assert(!HasPrev<ForwardSubrange>::value, "");
static_assert(!HasPrev<ForwardSubrange &>::value, "");
static_assert(!HasPrev<ForwardSubrange const&>::value, "");
static_assert(!HasPrev<ForwardSubrange &&>::value, "");
static_assert(!HasPrev<ForwardSubrange const&&>::value, "");
static_assert( HasPrev<BidirectionalSubrange>::value, "");
static_assert( HasPrev<BidirectionalSubrange &>::value, "");
static_assert( HasPrev<BidirectionalSubrange const&>::value, "");
static_assert( HasPrev<BidirectionalSubrange &&>::value, "");
static_assert( HasPrev<BidirectionalSubrange const&&>::value, "");
static_assert( HasPrev<RandomAccessSubrange>::value, "");
static_assert( HasPrev<RandomAccessSubrange &>::value, "");
static_assert( HasPrev<RandomAccessSubrange const&>::value, "");
static_assert( HasPrev<RandomAccessSubrange &&>::value, "");
static_assert( HasPrev<RandomAccessSubrange const&&>::value, "");

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int x[] = {1, 2, 3, 4, 5};

	hamon::ranges::subrange<int*> const sr(x, x+5);
	VERIFY(sr.begin() == x);
	VERIFY(sr.size() == 5);

	auto sr2 = sr.next();
	VERIFY(sr2.begin() == x+1);
	VERIFY(sr2.size() == 4);

	auto sr3 = sr.next().next(2);
	VERIFY(sr3.begin() == x+3);
	VERIFY(sr3.size() == 2);

	auto sr4 = sr.next(4).prev();
	VERIFY(sr4.begin() == x+3);
	VERIFY(sr4.size() == 2);

	auto sr5 = sr.next(4).prev(2);
	VERIFY(sr5.begin() == x+2);
	VERIFY(sr5.size() == 3);

	return true;
}

GTEST_TEST(RangesTest, SubrangeNextPrevTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

#undef VERIFY

}	// namespace next_prev_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
