/**
 *	@file	unit_test_basic_const_iterator_bracket.cpp
 *
 *	@brief	operator[] のテスト
 * 
 *	constexpr reference operator[](difference_type n) const
 *		requires random_access_iterator<Iterator>;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
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

namespace bracket_test
{

#if 0//defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept index_accessible =
	requires(Iter i, hamon::iter_difference_t<Iter> n)
	{
		{ i[n] } -> hamon::same_as<hamon::iter_const_reference_t<Iter>>;
	};

template <typename Iter>
using index_accessible_t =
	hamon::bool_constant<index_accessible<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct index_accessible
{
private:
	template <typename I2,
		typename D = hamon::iter_difference_t<I2>,
		typename T = decltype(hamon::declval<I2&>()[hamon::declval<D>()])>
	static auto test(int) -> hamon::same_as_t<T, hamon::iter_const_reference_t<I2>>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using index_accessible_t =
	typename detail::index_accessible<Iter>::type;

#endif

static_assert(!index_accessible_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!index_accessible_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!index_accessible_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( index_accessible_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( index_accessible_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = random_access_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{a}};

	VERIFY(3 == ci[0]);
	VERIFY(1 == ci[1]);
	VERIFY(4 == ci[2]);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, BracketTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace bracket_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
