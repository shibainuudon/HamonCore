/**
 *	@file	unit_test_basic_const_iterator_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	friend constexpr basic_const_iterator operator-(const basic_const_iterator& i, difference_type n)
 *		requires random_access_iterator<Iterator>;
 *	
 *	template<sized_sentinel_for<Iterator> S>
 *	constexpr difference_type operator-(const S& y) const;
 *	
 *	template<not-a-const-iterator S>
 *		requires sized_sentinel_for<S, Iterator>
 *	friend constexpr difference_type operator-(const S& x, const basic_const_iterator& y);
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace sub_test
{

#if 0//defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept subtractable1 =
	requires(Iter const& i, hamon::iter_difference_t<Iter> n)
	{
		{ i - n } -> hamon::same_as<Iter>;
	};

template <typename Iter, typename Sent>
concept subtractable2 =
	requires(Iter const& i, Sent const& s)
	{
		{ i - s } -> hamon::same_as<hamon::iter_difference_t<Iter>>;
		{ s - i } -> hamon::same_as<hamon::iter_difference_t<Iter>>;
	};

template <typename Iter>
using subtractable1_t = hamon::bool_constant<subtractable1<Iter>>;
template <typename Iter, typename Sent>
using subtractable2_t = hamon::bool_constant<subtractable2<Iter, Sent>>;

#else

namespace detail
{

template <typename Iter>
struct subtractable1
{
private:
	template <typename I2,
		typename D = hamon::iter_difference_t<I2>,
		typename T = decltype(hamon::declval<I2 const&>() - hamon::declval<D>())>
	static auto test(int) -> hamon::same_as_t<T, I2>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

template <typename Iter, typename Sent>
struct subtractable2
{
private:
	template <typename I2, typename S2,
		typename D = hamon::iter_difference_t<I2>,
		typename T1 = decltype(hamon::declval<I2 const&>() - hamon::declval<S2 const&>()),
		typename T2 = decltype(hamon::declval<S2 const&>() - hamon::declval<I2 const&>())>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as_t<T1, hamon::iter_difference_t<I2>>,
		hamon::same_as_t<T2, hamon::iter_difference_t<I2>>
	>;

	template <typename I2, typename S2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter, Sent>(0));
};

}	// namespace detail

template <typename Iter>
using subtractable1_t = typename detail::subtractable1<Iter>::type;
template <typename Iter, typename Sent>
using subtractable2_t = typename detail::subtractable2<Iter, Sent>::type;

#endif

static_assert(!subtractable1_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!subtractable1_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!subtractable1_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( subtractable1_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( subtractable1_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(!subtractable2_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>,         input_iterator_wrapper<int>>::value, "");
static_assert(!subtractable2_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>,       forward_iterator_wrapper<int>>::value, "");
static_assert(!subtractable2_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>, bidirectional_iterator_wrapper<int>>::value, "");
static_assert( subtractable2_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>, random_access_iterator_wrapper<int>>::value, "");
static_assert( subtractable2_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>,    contiguous_iterator_wrapper<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = random_access_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	Iter first{&a[0]};
	Iter last {&a[2]};
	hamon::basic_const_iterator<Iter> ci1{first};
	hamon::basic_const_iterator<Iter> ci2{last};

	auto ci3 = ci2 - 1;
	auto ci4 = ci2 - 2;
	VERIFY(1 == *ci3);
	VERIFY(3 == *ci4);

	VERIFY(-2 == ci1 - ci2);
	VERIFY( 2 == ci2 - ci1);

	VERIFY( 0 == ci1 - first);
	VERIFY(-2 == ci1 - last);
	VERIFY( 2 == ci2 - first);
	VERIFY( 0 == ci2 - last);

	VERIFY( 0 == first - ci1);
	VERIFY( 2 == last  - ci1);
	VERIFY(-2 == first - ci2);
	VERIFY( 0 == last  - ci2);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, SubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace sub_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
