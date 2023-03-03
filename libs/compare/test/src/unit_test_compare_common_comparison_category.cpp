/**
 *	@file	unit_test_compare_common_comparison_category.cpp
 *
 *	@brief	common_comparison_category のテスト
 */

#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon_compare_test
{

namespace common_comparison_category_test
{

using hamon::common_comparison_category_t;
using hamon::partial_ordering;
using hamon::weak_ordering;
using hamon::strong_ordering;

static_assert(hamon::is_same<strong_ordering,  common_comparison_category_t<>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<int>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<int, int>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<partial_ordering, int>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<weak_ordering, int>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<strong_ordering, int>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<int, partial_ordering>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<int, weak_ordering>>(), "");
static_assert(hamon::is_same<void,             common_comparison_category_t<int, strong_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<partial_ordering>>(), "");
static_assert(hamon::is_same<weak_ordering,    common_comparison_category_t<weak_ordering>>(), "");
static_assert(hamon::is_same<strong_ordering,  common_comparison_category_t<strong_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<partial_ordering, partial_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<partial_ordering, weak_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<partial_ordering, strong_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<weak_ordering, partial_ordering>>(), "");
static_assert(hamon::is_same<weak_ordering,    common_comparison_category_t<weak_ordering, weak_ordering>>(), "");
static_assert(hamon::is_same<weak_ordering,    common_comparison_category_t<weak_ordering, strong_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<strong_ordering, partial_ordering>>(), "");
static_assert(hamon::is_same<weak_ordering,    common_comparison_category_t<strong_ordering, weak_ordering>>(), "");
static_assert(hamon::is_same<strong_ordering,  common_comparison_category_t<strong_ordering, strong_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<strong_ordering, partial_ordering, strong_ordering, strong_ordering>>(), "");
static_assert(hamon::is_same<partial_ordering, common_comparison_category_t<strong_ordering, partial_ordering, strong_ordering, weak_ordering>>(), "");
static_assert(hamon::is_same<weak_ordering,    common_comparison_category_t<strong_ordering, weak_ordering,    strong_ordering, weak_ordering>>(), "");
static_assert(hamon::is_same<strong_ordering,  common_comparison_category_t<strong_ordering, strong_ordering,  strong_ordering, strong_ordering>>(), "");

}	// namespace common_comparison_category_test

}	// namespace hamon_compare_test
