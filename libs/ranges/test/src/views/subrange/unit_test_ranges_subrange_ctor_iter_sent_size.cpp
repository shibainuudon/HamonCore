/**
 *	@file	unit_test_ranges_subrange_ctor_iter_sent_size.cpp
 *
 *	@brief	ranges::subrange のイテレータとセンチネルとサイズを取るコンストラクタのテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
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
namespace ctor_iter_sent_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using ForwardRange = test_forward_range<int>;

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

using RandomAccessRange = test_random_access_range<int>;

using RandomAccessSizedSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<RandomAccessRange>,
		hamon::ranges::sentinel_t<RandomAccessRange>,
		hamon::ranges::subrange_kind::sized
	>;

// subrange_kind::unsized のときは
// イテレータとセンチネルとサイズでコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	hamon::ranges::sentinel_t<ForwardRange>,
	std::size_t
>::value, "");

// subrange_kind::sized のときは
// イテレータとセンチネルとサイズでコンストラクトできる
static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	hamon::ranges::sentinel_t<ForwardRange>,
	std::size_t
>::value, "");

static_assert( hamon::is_constructible<
	RandomAccessSizedSubrange,
	hamon::ranges::iterator_t<RandomAccessRange>,
	hamon::ranges::sentinel_t<RandomAccessRange>,
	std::size_t
>::value, "");

// 引数の型が違うときはコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	int*,
	hamon::ranges::sentinel_t<ForwardRange>,
	std::size_t
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	hamon::ranges::iterator_t<ForwardRange>,
	std::size_t
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	int*,
	std::size_t
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

	template <bool B = Convertible,
		typename = hamon::enable_if_t<B>>
	constexpr operator BaseIter() const
	{
		return m_base;
	}
};

// イテレータにスライシングを起こさずに変換可能な場合はコンストラクトできる
static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, true>,
	hamon::ranges::sentinel_t<ForwardRange>,
	std::size_t
>::value, "");
static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, true>,
	std::size_t
>::value, "");

static_assert( hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, true>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, true>,
	std::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, false>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, true>,
	std::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, true>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, false>,
	std::size_t
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, false>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, false>,
	std::size_t
>::value, "");


template <bool NoExcept> 
struct ThrowIterator
{
	using difference_type = std::ptrdiff_t;
	ThrowIterator();
	ThrowIterator(ThrowIterator const&) noexcept(NoExcept);
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
	ThrowSentinel();
	ThrowSentinel(ThrowSentinel const&) noexcept(NoExcept);
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
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<true>, ThrowSentinel<true>, std::size_t
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<false>, ThrowSentinel<true>, std::size_t
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<true>, ThrowSentinel<false>, std::size_t
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<false>, ThrowSentinel<false>, std::size_t
>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
// イテレータとセンチネルが例外を投げずにコンストラクト可能なときは例外を投げない
static_assert( hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<true>, ThrowSentinel<true>, std::size_t
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<true>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<false>, ThrowSentinel<true>, std::size_t
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<true>, ThrowSentinel<false>, std::size_t
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<false>, hamon::ranges::subrange_kind::sized>,
	ThrowIterator<false>, ThrowSentinel<false>, std::size_t
>::value, "");
#endif

template <bool NoExcept> 
struct ThrowSizedSentinel
{
	ThrowSizedSentinel();
	ThrowSizedSentinel(ThrowSizedSentinel const&) noexcept(NoExcept);
};
template <bool B1, bool B2>
bool operator==(ThrowIterator<B1> const&, ThrowSizedSentinel<B2> const&);
template <bool B1, bool B2>
bool operator==(ThrowSizedSentinel<B1> const&, ThrowIterator<B2> const&);
template <bool B1, bool B2>
bool operator!=(ThrowIterator<B1> const&, ThrowSizedSentinel<B2> const&);
template <bool B1, bool B2>
bool operator!=(ThrowSizedSentinel<B1> const&, ThrowIterator<B2> const&);
template <bool B1, bool B2>
std::ptrdiff_t operator-(const ThrowSizedSentinel<B1>&, const ThrowIterator<B2>&);
template <bool B1, bool B2>
std::ptrdiff_t operator-(const ThrowIterator<B1>&, const ThrowSizedSentinel<B2>&);

static_assert(hamon::sized_sentinel_for_t<ThrowSizedSentinel<true>,  ThrowIterator<true>>::value, "");
static_assert(hamon::sized_sentinel_for_t<ThrowSizedSentinel<false>, ThrowIterator<true>>::value, "");
static_assert(hamon::sized_sentinel_for_t<ThrowSizedSentinel<true>,  ThrowIterator<false>>::value, "");
static_assert(hamon::sized_sentinel_for_t<ThrowSizedSentinel<false>, ThrowIterator<false>>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
static_assert( hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSizedSentinel<true>>,
	ThrowIterator<true>, ThrowSizedSentinel<true>, std::size_t
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSizedSentinel<true>>,
	ThrowIterator<false>, ThrowSizedSentinel<true>, std::size_t
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSizedSentinel<false>>,
	ThrowIterator<true>, ThrowSizedSentinel<false>, std::size_t
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSizedSentinel<false>>,
	ThrowIterator<false>, ThrowSizedSentinel<false>, std::size_t
>::value, "");
#endif

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardSizedSubrange sr(r.begin(), r.end(), 5);
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
		VERIFY(sr.size() == 5);
	}
	{
		int x[] = {1, 2, 3, 4, 5};
		RandomAccessRange r{x};
		RandomAccessSizedSubrange sr(r.begin(), r.end(), 5);
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
		VERIFY(sr.size() == 5);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardSizedSubrange sr(
			ConvertibleIter<forward_iterator_wrapper<int>, true>(r.begin()),
			r.end(),
			5);
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeCtorIterSentSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

#undef VERIFY

}	// namespace ctor_iter_sent_size_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
