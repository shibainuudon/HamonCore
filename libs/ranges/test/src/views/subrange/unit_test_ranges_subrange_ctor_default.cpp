/**
 *	@file	unit_test_ranges_subrange_ctor_default.cpp
 *
 *	@brief	ranges::subrange のデフォルトコンストラクタのテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NoDefaultIterator
{
	using difference_type = hamon::ptrdiff_t;
	NoDefaultIterator() = delete;
	NoDefaultIterator& operator++();
	void operator++(int);
	int& operator*() const;
	friend bool operator==(NoDefaultIterator const&, NoDefaultIterator const&);
	friend bool operator!=(NoDefaultIterator const&, NoDefaultIterator const&);
};
static_assert(hamon::input_or_output_iterator_t<NoDefaultIterator>::value, "");

struct NoDefaultSentinel
{
	friend bool operator==(NoDefaultIterator const&, NoDefaultSentinel const&);
	friend bool operator==(NoDefaultSentinel const&, NoDefaultIterator const&);
	friend bool operator!=(NoDefaultIterator const&, NoDefaultSentinel const&);
	friend bool operator!=(NoDefaultSentinel const&, NoDefaultIterator const&);
};

static_assert(!hamon::is_default_constructible<
	hamon::ranges::subrange<
		NoDefaultIterator,
		NoDefaultSentinel,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(!hamon::is_default_constructible<
	hamon::ranges::subrange<
		NoDefaultIterator,
		NoDefaultSentinel,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

struct ThrowDefaultIterator
{
	using difference_type = hamon::ptrdiff_t;
	ThrowDefaultIterator();
	ThrowDefaultIterator& operator++();
	void operator++(int);
	int& operator*() const;
	friend bool operator==(ThrowDefaultIterator const&, ThrowDefaultIterator const&);
	friend bool operator!=(ThrowDefaultIterator const&, ThrowDefaultIterator const&);
};
static_assert(hamon::input_or_output_iterator_t<ThrowDefaultIterator>::value, "");

struct ThrowDefaultSentinel
{
	friend bool operator==(ThrowDefaultIterator const&, ThrowDefaultSentinel const&);
	friend bool operator==(ThrowDefaultSentinel const&, ThrowDefaultIterator const&);
	friend bool operator!=(ThrowDefaultIterator const&, ThrowDefaultSentinel const&);
	friend bool operator!=(ThrowDefaultSentinel const&, ThrowDefaultIterator const&);
};

static_assert( hamon::is_default_constructible<
	hamon::ranges::subrange<
		ThrowDefaultIterator,
		ThrowDefaultSentinel,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert( hamon::is_default_constructible<
	hamon::ranges::subrange<
		ThrowDefaultIterator,
		ThrowDefaultSentinel,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		ThrowDefaultIterator,
		ThrowDefaultSentinel,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		ThrowDefaultIterator,
		ThrowDefaultSentinel,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

// int*
static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		int*,
		int*,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		int*,
		int*,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

// test_contiguous_range
static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		contiguous_iterator_wrapper<int>,
		test_sentinel<contiguous_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		contiguous_iterator_wrapper<int>,
		test_sentinel<contiguous_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

// test_random_access_range
static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		random_access_iterator_wrapper<int>,
		test_sentinel<random_access_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		random_access_iterator_wrapper<int>,
		test_sentinel<random_access_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

// test_bidirectional_range
static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		bidirectional_iterator_wrapper<int>,
		test_sentinel<bidirectional_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		bidirectional_iterator_wrapper<int>,
		test_sentinel<bidirectional_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		bidirectional_iterator_wrapper<int>,
		test_sentinel<bidirectional_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		bidirectional_iterator_wrapper<int>,
		test_sentinel<bidirectional_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

// test_forward_range
static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		forward_iterator_wrapper<int>,
		test_sentinel<forward_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		forward_iterator_wrapper<int>,
		test_sentinel<forward_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		forward_iterator_wrapper<int>,
		test_sentinel<forward_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		forward_iterator_wrapper<int>,
		test_sentinel<forward_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

// test_input_range
static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		input_iterator_wrapper<int>,
		test_sentinel<input_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_default_constructible<
	hamon::ranges::subrange<
		input_iterator_wrapper<int>,
		test_sentinel<input_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		input_iterator_wrapper<int>,
		test_sentinel<input_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::sized
	>
>::value, "");

static_assert(hamon::is_nothrow_default_constructible<
	hamon::ranges::subrange<
		input_iterator_wrapper<int>,
		test_sentinel<input_iterator_wrapper<int>>,
		hamon::ranges::subrange_kind::unsized
	>
>::value, "");

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = contiguous_iterator_wrapper<int>;
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	using Iter = random_access_iterator_wrapper<int>;
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	using Iter = bidirectional_iterator_wrapper<int>;
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::unsized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	using Iter = forward_iterator_wrapper<int>;
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::unsized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	using Iter = input_iterator_wrapper<int>;
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	{
		hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::unsized> sr;
		VERIFY(sr.begin() == Iter());
		VERIFY(sr.end() == Iter());
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

#undef VERIFY

}	// namespace ctor_default_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
