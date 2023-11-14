/**
 *	@file	unit_test_basic_const_iterator_add.cpp
 *
 *	@brief	operator+ のテスト
 *
 *	friend constexpr basic_const_iterator operator+(const basic_const_iterator& i, difference_type n)
 *		requires random_access_iterator<Iterator>;
 *
 *	friend constexpr basic_const_iterator operator+(difference_type n, const basic_const_iterator& i)
 *		requires random_access_iterator<Iterator>;
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

namespace add_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept addable1 =
	requires(Iter const& i, hamon::iter_difference_t<Iter> n)
	{
		{ i + n } -> hamon::same_as<Iter>;
	};
template <typename Iter>
concept addable2 =
	requires(Iter const& i, hamon::iter_difference_t<Iter> n)
	{
		{ n + i } -> hamon::same_as<Iter>;
	};

template <typename Iter>
using addable1_t = hamon::bool_constant<addable1<Iter>>;
template <typename Iter>
using addable2_t = hamon::bool_constant<addable2<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct addable1
{
private:
	template <typename I2,
		typename D = hamon::iter_difference_t<I2>,
		typename T = decltype(hamon::declval<I2 const&>() + hamon::declval<D>())>
	static auto test(int) -> hamon::same_as_t<T, I2>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

template <typename Iter>
struct addable2
{
private:
	template <typename I2,
		typename D = hamon::iter_difference_t<I2>,
		typename T = decltype(hamon::declval<D>() + hamon::declval<I2 const&>())>
	static auto test(int) -> hamon::same_as_t<T, I2>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using addable1_t = typename detail::addable1<Iter>::type;
template <typename Iter>
using addable2_t = typename detail::addable2<Iter>::type;

#endif

static_assert(!addable1_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!addable1_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!addable1_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( addable1_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( addable1_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(!addable2_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!addable2_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!addable2_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( addable2_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( addable2_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = random_access_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{a}};

	auto ci2 = ci + 2;
	VERIFY(4 == *ci2);

	auto ci3 = 1 + ci;
	VERIFY(1 == *ci3);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, AddTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace add_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
