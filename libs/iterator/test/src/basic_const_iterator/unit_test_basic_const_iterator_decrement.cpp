/**
 *	@file	unit_test_basic_const_iterator_decrement.cpp
 *
 *	@brief	デクリメントのテスト
 * 
 *	constexpr basic_const_iterator& operator--() requires bidirectional_iterator<Iterator>;
 *	constexpr basic_const_iterator operator--(int) requires bidirectional_iterator<Iterator>;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/concepts.hpp>
#include <hamon/concepts.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace decrement_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept pre_decrementable =
	requires(Iter i)
	{
		{ --i } -> hamon::same_as<Iter&>;
	};

template <typename Iter>
concept post_decrementable =
	requires(Iter i)
	{
		{ i-- } -> hamon::same_as<Iter>;
	};

template <typename Iter>
using pre_decrementable_t =
	hamon::bool_constant<pre_decrementable<Iter>>;

template <typename Iter>
using post_decrementable_t =
	hamon::bool_constant<post_decrementable<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct pre_decrementable
{
private:
	template <typename I2, typename T = decltype(--hamon::declval<I2&>())>
	static auto test(int) -> hamon::same_as_t<T, I2&>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

template <typename Iter>
struct post_decrementable
{
private:
	template <typename I2, typename T = decltype(hamon::declval<I2&>()--)>
	static auto test(int) -> hamon::same_as_t<T, I2>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using pre_decrementable_t =
	typename detail::pre_decrementable<Iter>::type;

template <typename Iter>
using post_decrementable_t =
	typename detail::post_decrementable<Iter>::type;

#endif

static_assert(!pre_decrementable_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!pre_decrementable_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( pre_decrementable_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( pre_decrementable_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( pre_decrementable_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(!post_decrementable_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!post_decrementable_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( post_decrementable_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( post_decrementable_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( post_decrementable_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = bidirectional_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{&a[2]}};

	auto t1 = --ci;

	VERIFY(1 == *ci);
	VERIFY(1 == *t1);

	auto t2 = ci--;

	VERIFY(3 == *ci);
	VERIFY(1 == *t2);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, DecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace decrement_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
