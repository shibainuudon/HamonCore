/**
 *	@file	unit_test_ranges_subrange_ctor_range.cpp
 *
 *	@brief	ranges::subrange のRangeを取るコンストラクタのテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace ctor_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using ForwardRange             = test_forward_range<int>;
using ForwardSizedRange        = test_forward_sized_range<int>;
using ForwardBorrowdRange      = test_forward_borrowed_range<int>;
using ForwardSizedBorrowdRange = test_forward_sized_borrowed_range<int>;
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
	ForwardUnsizedSubrange,
	ForwardRange
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	ForwardSizedRange
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ForwardRange
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ForwardSizedRange
>::value, "");
static_assert(!hamon::is_constructible<
	RandomAccessSubrange,
	RandomAccessRange
>::value, "");

// borrowed range である range からはコンストラクトできる
static_assert( hamon::is_constructible<
	ForwardUnsizedSubrange,
	ForwardBorrowdRange
>::value, "");
static_assert( hamon::is_constructible<
	RandomAccessSubrange,
	RandomAccessBorrowdRange
>::value, "");

// subrange_kind::sized かつ sized_range<Range> == false のときは
// コンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ForwardBorrowdRange
>::value, "");

// subrange_kind::sized かつ sized_range<Range> == true のときは
// コンストラクトできる
static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	ForwardSizedBorrowdRange
>::value, "");

// イテレータとセンチネルの型が合わない場合はコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	RandomAccessBorrowdRange
>::value, "");
static_assert(!hamon::is_constructible<
	RandomAccessSubrange,
	ForwardBorrowdRange
>::value, "");

template <typename BaseIter, bool Convertible>
struct ConvertibleIter
{
	BaseIter m_base;

	constexpr ConvertibleIter() = default;

	constexpr ConvertibleIter(int*) {}

	template <typename U, bool B>
	constexpr ConvertibleIter(ConvertibleIter<U, B> const&) {}

	constexpr explicit
	ConvertibleIter(BaseIter it)
		: m_base(it)
	{}

	template <bool B = Convertible,
		typename = hamon::enable_if_t<B>>
	constexpr operator BaseIter() const
	{
		return m_base;
	}

	using difference_type = std::ptrdiff_t;
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
template <bool B1, bool B2>
using ConvertibleSizedBorrowedRange =
	test_sized_borrowed_range<
		int,
		ConvertibleIter<hamon::ranges::iterator_t<ForwardRange>, B1>,
		ConvertibleIter<hamon::ranges::sentinel_t<ForwardRange>, B2>
	>;

static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleBorrowedRange<true,  true>>::value, "");
static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleBorrowedRange<false, true>>::value, "");
static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleBorrowedRange<true,  false>>::value, "");
static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleBorrowedRange<false, false>>::value, "");

static_assert( hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleBorrowedRange<true,  true>>::value, "");
static_assert(!hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleBorrowedRange<false, true>>::value, "");
static_assert(!hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleBorrowedRange<true,  false>>::value, "");
static_assert(!hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleBorrowedRange<false, false>>::value, "");

static_assert( hamon::is_constructible<ForwardSizedSubrange, ConvertibleSizedBorrowedRange<true,  true>>::value, "");
static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleSizedBorrowedRange<false, true>>::value, "");
static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleSizedBorrowedRange<true,  false>>::value, "");
static_assert(!hamon::is_constructible<ForwardSizedSubrange, ConvertibleSizedBorrowedRange<false, false>>::value, "");

static_assert( hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleSizedBorrowedRange<true,  true>>::value, "");
static_assert(!hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleSizedBorrowedRange<false, true>>::value, "");
static_assert(!hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleSizedBorrowedRange<true,  false>>::value, "");
static_assert(!hamon::is_constructible<ForwardUnsizedSubrange, ConvertibleSizedBorrowedRange<false, false>>::value, "");

template <bool NoExcept> 
struct ThrowIterator
{
	using difference_type = std::ptrdiff_t;
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

template <typename T, typename Iterator, typename Sentinel = test_sentinel<Iterator>>
struct throw_sized_borrowed_range : public test_range<T, Iterator, Sentinel>
{
	using base_t = test_range<T, Iterator, Sentinel>;
	using base_t::test_range;

	HAMON_CONSTEXPR hamon::size_t size() const
	{
		return static_cast<hamon::size_t>(base_t::m_last - base_t::m_first);
	}
};

}}}

#include <hamon/ranges/concepts/enable_borrowed_range.hpp>

HAMON_RANGES_START_NAMESPACE
template <typename T, typename Iterator, typename Sentinel>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true,
	hamon_ranges_test::subrange_test::ctor_range_test::throw_sized_borrowed_range<T, Iterator, Sentinel>);
HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace ctor_range_test
{

static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>
>::value, "");
static_assert( hamon::is_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>
>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
// イテレータとセンチネルが例外を投げずにコンストラクト可能なときは例外を投げない
static_assert( hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::unsized>,
	test_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>
>::value, "");

static_assert( hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	test_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<true>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<true>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<true>, ThrowSentinel<false>>
>::value, "");
static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange< ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	throw_sized_borrowed_range<int, ThrowIterator<false>, ThrowSentinel<false>>
>::value, "");
#endif

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardUnsizedSubrange sr(ForwardBorrowdRange{x});
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardSizedSubrange sr(ForwardSizedBorrowdRange{x});
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		int x[] = {1, 2, 3, 4, 5, 6};
		RandomAccessSubrange sr(RandomAccessBorrowdRange{x});
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+6);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeCtorRangeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace ctor_range_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
