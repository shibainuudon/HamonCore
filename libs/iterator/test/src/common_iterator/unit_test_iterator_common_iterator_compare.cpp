/**
 *	@file	unit_test_iterator_common_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class I2, sentinel_for<I> S2>
 *		requires sentinel_for<S, I2>
 *	friend constexpr bool operator==(
 *		const common_iterator& x, const common_iterator<I2, S2>& y);
 *
 *	template<class I2, sentinel_for<I> S2>
 *		requires sentinel_for<S, I2> && equality_comparable_with<I, I2>
 *	friend constexpr bool operator==(
 *		const common_iterator& x, const common_iterator<I2, S2>& y);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace compare_test {

template <typename T, typename U = T, typename = void>
struct has_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_eq<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_neq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_neq<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

static_assert( has_eq<
	hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>,
	hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>
>::value, "");

static_assert(!has_eq<
	hamon::common_iterator<input_iterator_wrapper<int const>, test_sentinel<input_iterator_wrapper<int const>>>,
	hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>
>::value, "");

static_assert( has_eq<
	hamon::common_iterator<input_iterator_wrapper<int const>, hamon::unreachable_sentinel_t>,
	hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>
>::value, "");

static_assert( has_neq<
	hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>,
	hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>
>::value, "");

static_assert(!has_neq<
	hamon::common_iterator<input_iterator_wrapper<int const>, test_sentinel<input_iterator_wrapper<int const>>>,
	hamon::common_iterator<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>
>::value, "");

static_assert( has_neq<
	hamon::common_iterator<input_iterator_wrapper<int const>, hamon::unreachable_sentinel_t>,
	hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>
>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using I = int*;
	using S = int const*;
	using CI = hamon::common_iterator<I, S>;
	int a[] = {1, 2, 3};
	CI it1{I{&a[0]}};
	CI it2{I{&a[1]}};
	CI it3{S{&a[0]}};
	CI it4{S{&a[1]}};

	VERIFY( (it1 == it1));
	VERIFY(!(it1 == it2));
	VERIFY( (it1 == it3));
	VERIFY(!(it1 == it4));

	VERIFY(!(it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));
	VERIFY( (it2 == it4));

	VERIFY( (it3 == it1));
	VERIFY(!(it3 == it2));
	VERIFY( (it3 == it3));
	VERIFY( (it3 == it4));

	VERIFY(!(it4 == it1));
	VERIFY( (it4 == it2));
	VERIFY( (it4 == it3));
	VERIFY( (it4 == it4));

	VERIFY(!(it1 != it1));
	VERIFY( (it1 != it2));
	VERIFY(!(it1 != it3));
	VERIFY( (it1 != it4));

	VERIFY( (it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));
	VERIFY(!(it2 != it4));

	VERIFY(!(it3 != it1));
	VERIFY( (it3 != it2));
	VERIFY(!(it3 != it3));
	VERIFY(!(it3 != it4));

	VERIFY( (it4 != it1));
	VERIFY(!(it4 != it2));
	VERIFY(!(it4 != it3));
	VERIFY(!(it4 != it4));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using I = input_or_output_iterator_wrapper<int>;
	using S = test_sentinel<I>;
	using CI = hamon::common_iterator<I, S>;
	int a[] = {1, 2, 3};
	CI it1{I{&a[0]}};
	CI it2{I{&a[1]}};
	CI it3{S{I{&a[0]}}};
	CI it4{S{I{&a[1]}}};

	VERIFY( (it1 == it1));
	VERIFY( (it1 == it2));
	VERIFY( (it1 == it3));
	VERIFY(!(it1 == it4));

	VERIFY( (it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));
	VERIFY( (it2 == it4));

	VERIFY( (it3 == it1));
	VERIFY(!(it3 == it2));
	VERIFY( (it3 == it3));
	VERIFY( (it3 == it4));

	VERIFY(!(it4 == it1));
	VERIFY( (it4 == it2));
	VERIFY( (it4 == it3));
	VERIFY( (it4 == it4));

	VERIFY(!(it1 != it1));
	VERIFY(!(it1 != it2));
	VERIFY(!(it1 != it3));
	VERIFY( (it1 != it4));

	VERIFY(!(it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));
	VERIFY(!(it2 != it4));

	VERIFY(!(it3 != it1));
	VERIFY( (it3 != it2));
	VERIFY(!(it3 != it3));
	VERIFY(!(it3 != it4));

	VERIFY( (it4 != it1));
	VERIFY(!(it4 != it2));
	VERIFY(!(it4 != it3));
	VERIFY(!(it4 != it4));

	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, CompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace compare_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
