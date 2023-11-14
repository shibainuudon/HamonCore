/**
 *	@file	unit_test_basic_const_iterator_sub_assign.cpp
 *
 *	@brief	operator-= のテスト
 * 
 *	constexpr basic_const_iterator& operator-=(difference_type n)
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

namespace sub_assign_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept sub_assignable =
	requires(Iter i, hamon::iter_difference_t<Iter> n)
	{
		{ i -= n } -> hamon::same_as<Iter&>;
	};

template <typename Iter>
using sub_assignable_t =
	hamon::bool_constant<sub_assignable<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct sub_assignable
{
private:
	template <typename I2,
		typename D = hamon::iter_difference_t<I2>,
		typename T = decltype(hamon::declval<I2&>() -= hamon::declval<D>())>
	static auto test(int) -> hamon::same_as_t<T, I2&>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using sub_assignable_t =
	typename detail::sub_assignable<Iter>::type;

#endif

static_assert(!sub_assignable_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert(!sub_assignable_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert(!sub_assignable_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( sub_assignable_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( sub_assignable_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = random_access_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{&a[2]}};

	VERIFY(4 == *ci);

	auto t = (ci -= 2);

	VERIFY(3 == *ci);
	VERIFY(3 == *t);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, SubAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace sub_assign_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
