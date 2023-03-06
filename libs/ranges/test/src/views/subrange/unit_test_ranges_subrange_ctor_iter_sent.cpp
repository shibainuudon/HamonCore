/**
 *	@file	unit_test_ranges_subrange_ctor_iter_sent.cpp
 *
 *	@brief	ranges::subrange のイテレータとセンチネルを取るコンストラクタのテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
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
namespace ctor_iter_sent_test
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

// subrange_kind::unsized のときはイテレータとセンチネルでコンストラクトできる
static_assert( hamon::is_constructible<
	ForwardUnsizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	hamon::ranges::sentinel_t<ForwardRange>
>::value, "");

// subrange_kind::sized かつ sized_sentinel_for<Sent, It> == true のときは
// イテレータとセンチネルでコンストラクトできる
static_assert( hamon::is_constructible<
	RandomAccessSizedSubrange,
	hamon::ranges::iterator_t<RandomAccessRange>,
	hamon::ranges::sentinel_t<RandomAccessRange>
>::value, "");

// subrange_kind::sized かつ sized_sentinel_for<Sent, It> == false のときは
// イテレータとセンチネルでコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardSizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	hamon::ranges::sentinel_t<ForwardRange>
>::value, "");

// 引数の型が違うときはコンストラクトできない
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	int*,
	hamon::ranges::sentinel_t<ForwardRange>
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	hamon::ranges::iterator_t<ForwardRange>
>::value, "");

static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	int*
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
	ForwardUnsizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, true>,
	hamon::ranges::sentinel_t<ForwardRange>
>::value, "");
static_assert( hamon::is_constructible<
	ForwardUnsizedSubrange,
	hamon::ranges::iterator_t<ForwardRange>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, true>
>::value, "");

static_assert( hamon::is_constructible<
	ForwardUnsizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, true>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, true>
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, false>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, true>
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, true>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, false>
>::value, "");
static_assert(!hamon::is_constructible<
	ForwardUnsizedSubrange,
	ConvertibleIter<forward_iterator_wrapper<int>, false>,
	ConvertibleIter<test_sentinel<forward_iterator_wrapper<int>>, false>
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

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<true>>,
	ThrowIterator<true>, ThrowSentinel<true>
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<true>>,
	ThrowIterator<false>, ThrowSentinel<true>
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<false>>,
	ThrowIterator<true>, ThrowSentinel<false>
>::value, "");

static_assert( hamon::is_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<false>>,
	ThrowIterator<false>, ThrowSentinel<false>
>::value, "");

#if !defined(HAMON_USE_STD_RANGES)
// イテレータとセンチネルが例外を投げずにコンストラクト可能なときは例外を投げない
static_assert( hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<true>>,
	ThrowIterator<true>, ThrowSentinel<true>
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<true>>,
	ThrowIterator<false>, ThrowSentinel<true>
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<true>, ThrowSentinel<false>>,
	ThrowIterator<true>, ThrowSentinel<false>
>::value, "");

static_assert(!hamon::is_nothrow_constructible<
	hamon::ranges::subrange<ThrowIterator<false>, ThrowSentinel<false>>,
	ThrowIterator<false>, ThrowSentinel<false>
>::value, "");
#endif

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardUnsizedSubrange sr(r.begin(), r.end());
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
	}
	{
		int x[] = {1, 2, 3, 4, 5};
		RandomAccessRange r{x};
		RandomAccessSizedSubrange sr(r.begin(), r.end());
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
		ForwardUnsizedSubrange sr(ConvertibleIter<forward_iterator_wrapper<int>, true>(r.begin()), r.end());
		VERIFY(sr.begin().m_ptr == x);
		VERIFY(sr.end().m_it.m_ptr == x+5);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeCtorIterSentTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

#undef VERIFY

}	// namespace ctor_iter_sent_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
