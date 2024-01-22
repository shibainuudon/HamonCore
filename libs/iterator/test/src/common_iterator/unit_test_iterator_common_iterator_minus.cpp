/**
 *	@file	unit_test_iterator_common_iterator_minus.cpp
 *
 *	@brief	operator- のテスト
 *
 *	template<sized_sentinel_for<I> I2, sized_sentinel_for<I> S2>
 *		requires sized_sentinel_for<S, I2>
 *	friend constexpr iter_difference_t<I2> operator-(
 *		const common_iterator& x, const common_iterator<I2, S2>& y);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace minus_test {

template <typename Iterator>
struct TestSizedSentinel
{
	bool operator==(TestSizedSentinel const& i) const;
	bool operator==(Iterator const& i) const;
	bool operator!=(Iterator const& i) const;
};

template <typename Iterator>
bool operator==(Iterator const& i, TestSizedSentinel<Iterator> const& s);

template <typename Iterator>
bool operator!=(Iterator const& i, TestSizedSentinel<Iterator> const& s);

template <typename Iterator>
hamon::iter_difference_t<Iterator>
operator-(TestSizedSentinel<Iterator> const& s, Iterator const& i);

template <typename Iterator>
hamon::iter_difference_t<Iterator>
operator-(Iterator const& i, TestSizedSentinel<Iterator> const& s);

template <typename T, typename U, typename = void>
struct has_minus
	: public hamon::false_type {};

template <typename T, typename U>
struct has_minus<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

static_assert( has_minus<
	hamon::common_iterator<random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>,
	hamon::common_iterator<random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>
>::value, "");
static_assert(!has_minus<
	hamon::common_iterator<bidirectional_iterator_wrapper<int>, test_sentinel<bidirectional_iterator_wrapper<int>>>,
	hamon::common_iterator<bidirectional_iterator_wrapper<int>, test_sentinel<bidirectional_iterator_wrapper<int>>>
>::value, "");
static_assert(!has_minus<
	hamon::common_iterator<random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>,
	hamon::common_iterator<random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>
>::value, "");
static_assert(!has_minus<
	hamon::common_iterator<random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>,
	hamon::common_iterator<random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>
>::value, "");

static_assert( has_minus<
	hamon::common_iterator<random_access_iterator_wrapper<int>, TestSizedSentinel<random_access_iterator_wrapper<int>>>,
	hamon::common_iterator<random_access_iterator_wrapper<int>, TestSizedSentinel<random_access_iterator_wrapper<int>>>
>::value, "");
static_assert(!has_minus<
	hamon::common_iterator<bidirectional_iterator_wrapper<int>, TestSizedSentinel<bidirectional_iterator_wrapper<int>>>,
	hamon::common_iterator<bidirectional_iterator_wrapper<int>, TestSizedSentinel<bidirectional_iterator_wrapper<int>>>
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

	VERIFY((it1 - it1) ==  0);
	VERIFY((it1 - it2) == -1);
	VERIFY((it1 - it3) ==  0);
	VERIFY((it1 - it4) == -1);

	VERIFY((it2 - it1) ==  1);
	VERIFY((it2 - it2) ==  0);
	VERIFY((it2 - it3) ==  1);
	VERIFY((it2 - it4) ==  0);

	VERIFY((it3 - it1) ==  0);
	VERIFY((it3 - it2) == -1);
	VERIFY((it3 - it3) ==  0);
	VERIFY((it3 - it4) ==  0);

	VERIFY((it4 - it1) ==  1);
	VERIFY((it4 - it2) ==  0);
	VERIFY((it4 - it3) ==  0);
	VERIFY((it4 - it4) ==  0);

	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, MinusTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace minus_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
