/**
 *	@file	unit_test_pair_common_type.cpp
 *
 *	@brief	common_type のテスト
 */

#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/config.hpp>

namespace hamon_pair_test
{

namespace common_type_test
{

template <typename T, typename = void>
struct has_type : hamon::false_type { };

template <typename T>
struct has_type<T, hamon::void_t<typename T::type>>: hamon::true_type { };

template <typename... T>
constexpr bool
has_common_type()
{
	return has_type<hamon::common_type<T...>>::value;
}

static_assert( has_common_type<hamon::pair<int, int>, hamon::pair<int, int>>(), "");
static_assert(!has_common_type<hamon::pair<int, int>, hamon::pair<int, int*>>(), "");
static_assert( has_common_type<hamon::pair<int, int>, hamon::pair<int, int&>>(), "");
static_assert( has_common_type<hamon::pair<int, int>, hamon::pair<int, int&&>>(), "");
static_assert( has_common_type<hamon::pair<int, int>, hamon::pair<int, int const>>(), "");
static_assert(!has_common_type<hamon::pair<int, int>, hamon::pair<int, int const*>>(), "");
static_assert( has_common_type<hamon::pair<int, int>, hamon::pair<int, int const&>>(), "");
static_assert( has_common_type<hamon::pair<int, int>, hamon::pair<int, int const&&>>(), "");

template <typename T, typename U, typename Expected>
constexpr bool test_common_type()
{
	return
		hamon::same_as_t<hamon::common_type_t<T, U>, Expected>::value &&
		hamon::same_as_t<hamon::common_type_t<U, T>, Expected>::value;
}

static_assert(test_common_type<hamon::pair<int, int>, hamon::pair<int, int>, hamon::pair<int, int>>(), "");
static_assert(test_common_type<hamon::pair<int, long>, hamon::pair<long, int>, hamon::pair<long, long>>(), "");
static_assert(test_common_type<hamon::pair<const int, const long>, hamon::pair<const int, const long>, hamon::pair<int, long>>(), "");
static_assert(test_common_type<hamon::pair<const int&, const long&>, hamon::pair<const int&, const long&>, hamon::pair<int, long>>(), "");
static_assert(test_common_type<hamon::pair<const volatile int&, const volatile long&>, hamon::pair<const volatile long&, const volatile int&>, hamon::pair<long, long>>(), "");

}	// namespace common_type_test

}	// namespace hamon_pair_test
