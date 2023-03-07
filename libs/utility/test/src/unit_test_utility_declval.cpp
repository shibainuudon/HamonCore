/**
 *	@file	unit_test_utility_declval.cpp
 *
 *	@brief	declval のテスト
 */

#include <hamon/utility/declval.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon_utility_test
{

namespace declval_test
{

struct IncompleteType1;
struct IncompleteType2;

int   IncompleteFunction(IncompleteType1 const&);
float IncompleteFunction(IncompleteType2 const&) noexcept;

static_assert(hamon::is_same<decltype(IncompleteFunction(hamon::declval<IncompleteType1>())), int>::value, "");
static_assert(hamon::is_same<decltype(IncompleteFunction(hamon::declval<IncompleteType2>())), float>::value, "");
static_assert(!noexcept(IncompleteFunction(hamon::declval<IncompleteType1>())), "");
static_assert( noexcept(IncompleteFunction(hamon::declval<IncompleteType2>())), "");

static_assert(hamon::is_same<decltype(hamon::declval<int>()   * hamon::declval<int>()), int>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<float>() * hamon::declval<int>()), float>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<int>()   * hamon::declval<float>()), float>::value, "");
static_assert(hamon::is_same<decltype(hamon::declval<float>() * hamon::declval<float>()), float>::value, "");

}	// namespace declval_test

}	// namespace hamon_utility_test
