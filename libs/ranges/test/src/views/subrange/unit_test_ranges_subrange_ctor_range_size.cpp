/**
 *	@file	unit_test_ranges_subrange_ctor_range_size.cpp
 *
 *	@brief	ranges::subrange のRangeとサイズを取るコンストラクタのテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace ctor_range_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using ForwardRange             = test_forward_range<int>;
using ForwardBorrowdRange      = test_forward_borrowed_range<int>;
using RandomAccessRange        = test_random_access_range<int>;
using RandomAccessBorrowdRange = test_random_access_borrowed_range<int>;

using ForwardSizedSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<ForwardRange>,
		hamon::ranges::sentinel_t<ForwardRange>,
		hamon::ranges::subrange_kind::sized
	>;

using ForwardUnsizedSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<ForwardRange>,
		hamon::ranges::sentinel_t<ForwardRange>,
		hamon::ranges::subrange_kind::unsized
	>;

using RandomAccessSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<RandomAccessRange>,
		hamon::ranges::sentinel_t<RandomAccessRange>
	>;

// borrowed range でない range からはコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ForwardRange,
	hamon::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	ForwardRange,
	hamon::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	RandomAccessSubrange,
	RandomAccessRange,
	hamon::size_t
>::value, "");

// borrowed range である range からはコンストラクトできる
static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	ForwardBorrowdRange,
	hamon::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	ForwardBorrowdRange,
	hamon::size_t
>::value, "");
static_assert( hamon::is_constructible<
	RandomAccessSubrange,
	RandomAccessBorrowdRange,
	hamon::size_t
>::value, "");

// イテレータとセンチネルの型が合わない場合はコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	RandomAccessBorrowdRange,
	hamon::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	RandomAccessSubrange,
	ForwardBorrowdRange,
	hamon::size_t
>::value, "");

template <typename BaseIter, bool Convertible>
struct ConvertibleIter
{
	BaseIter m_base;

	constexpr ConvertibleIter() = default;

	constexpr explicit
	ConvertibleIter(BaseIter it)
		: m_base(it)
	{}

	constexpr ConvertibleIter(int*) {}

	template <typename U, bool B>
	constexpr ConvertibleIter(ConvertibleIter<U, B> const&) {}

	template <bool B = Convertible,
		typename = hamon::enable_if_t<B>>
	constexpr operator BaseIter() const
	{
		return m_base;
	}

	using difference_type = hamon::ptrdiff_t;
	ConvertibleIter& operator++();
	void operator++(int);
	int& operator*() const;
};
template <typename I1, bool B1, typename I2, bool B2>
bool operator==(ConvertibleIter<I1, B1> const&, ConvertibleIter<I2, B2> const&);
template <typename I1, bool B1, typename I2, bool B2>
bool operator!=(ConvertibleIter<I1, B1> const&, ConvertibleIter<I2, B2> const&);

// イテレータにスライシングを起こさずに変換可能な場合はコンストラクトできる

template <bool B1, bool B2>
using ConvertibleBorrowedRange =
	test_borrowed_range<
		int,
		ConvertibleIter<hamon::ranges::iterator_t<ForwardRange>, B1>,
		ConvertibleIter<hamon::ranges::sentinel_t<ForwardRange>, B2>
	>;

static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleBorrowedRange<true, true>,
	hamon::size_t
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleBorrowedRange<false, true>,
	hamon::size_t
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleBorrowedRange<true, false>,
	hamon::size_t
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleBorrowedRange<false, false>,
	hamon::size_t
>::value, "");

template <bool NoExcept> 
struct ThrowIterator
{
	using difference_type = hamon::ptrdiff_t;
	ThrowIterator() {}
	ThrowIterator(ThrowIterator const&) noexcept(NoExcept) {}
	ThrowIterator(int*) {}
	ThrowIterator& operator++();
	void operator++(int);
	int& operator*() const;
};
template <bool B1, bool B2>
bool operator==(ThrowIterator<B1> const&, ThrowIterator<B2> const&);
template <bool B1, bool B2>
bool operator!=(ThrowIterator<B1> const&, ThrowIterator<B2> const&);
static_assert(hamon::input_or_output_iterator_t<ThrowIterator<true>>::value, "");
static_assert(hamon::input_or_output_iterator_t<ThrowIterator<false>>::value, "");

template <bool NoExcept> 
struct ThrowSentinel
{
	ThrowSentinel() {}
	ThrowSentinel(ThrowSentinel const&) noexcept(NoExcept) {}
	template <bool B>
	ThrowSentinel(ThrowIterator<B> const&) {}
};
template <bool B1, bool B2>
bool operator==(ThrowIterator<B1> const&, ThrowSentinel<B2> const&);
template <bool B1, bool B2>
bool operator==(ThrowSentinel<B1> const&, ThrowIterator<B2> const&);
template <bool B1, bool B2>
bool operator!=(ThrowIterator<B1> const&, ThrowSentinel<B2> const&);
template <bool B1, bool B2>
bool operator!=(ThrowSentinel<B1> const&, ThrowIterator<B2> const&);

static_assert(!hamon::sized_sentinel_for_t<ThrowSentinel<true>,  ThrowIterator<true>>::value, "");
static_assert(!hamon::sized_sentinel_for_t<ThrowSentinel<false>, ThrowIterator<true>>::value, "");
static_assert(!hamon::sized_sentinel_for_t<ThrowSentinel<true>,  ThrowIterator<false>>::value, "");
static_assert(!hamon::sized_sentinel_for_t<ThrowSentinel<false>, ThrowIterator<false>>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>, hamon::size_t
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>, hamon::size_t
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>, hamon::size_t
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>, hamon::size_t
>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
// イテレータとセンチネルが例外を投げずにコンストラクト可能なときは例外を投げない
static_assert( hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>, hamon::size_t
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>, hamon::size_t
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>, hamon::size_t
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>, hamon::size_t
>::value, "");
#endif

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5, 6};
		RandomAccessBorrowdRange r(x, x);
		RandomAccessSubrange sr(r, 0);
		VERIFY(sr.size() == 0);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5, 6};
		RandomAccessSubrange sr(RandomAccessBorrowdRange{x}, 6);
		VERIFY(sr.size() == 6);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeCtorRangeSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

#undef VERIFY

}	// namespace ctor_range_size_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
