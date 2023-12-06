/**
 *	@file	unit_test_tuple_tuple_common_type.cpp
 *
 *	@brief	common_typeのテスト
 *
 *	template<tuple-like TTuple, tuple-like UTuple>
 *	struct common_type<TTuple, UTuple> {
 *	  using type = see below;
 *	};
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/config.hpp>

namespace hamon_tuple_test
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

static_assert( has_common_type<hamon::tuple<int>, hamon::tuple<int>>(), "");
static_assert(!has_common_type<hamon::tuple<int>, hamon::tuple<int*>>(), "");
static_assert( has_common_type<hamon::tuple<int>, hamon::tuple<int&>>(), "");
static_assert(!has_common_type<hamon::tuple<int>, hamon::tuple<int, int>>(), "");
static_assert( has_common_type<hamon::tuple<int, int>, hamon::tuple<int, int>>(), "");
static_assert( has_common_type<hamon::tuple<int>, hamon::array<int, 1>>(), "");
static_assert(!has_common_type<hamon::tuple<int>, hamon::array<int, 2>>(), "");
static_assert(!has_common_type<hamon::tuple<int*>, hamon::array<int, 1>>(), "");
static_assert(!has_common_type<hamon::tuple<int, int>, hamon::array<int, 1>>(), "");
static_assert( has_common_type<hamon::tuple<int, int>, hamon::array<int, 2>>(), "");
static_assert(!has_common_type<hamon::tuple<int>, hamon::pair<int, int>>(), "");
static_assert( has_common_type<hamon::tuple<int, int>, hamon::pair<int, int>>(), "");
static_assert(!has_common_type<hamon::tuple<int, int, int>, hamon::pair<int, int>>(), "");
static_assert( has_common_type<hamon::tuple<int*, int*>, hamon::ranges::subrange<int*, int*>>(), "");
static_assert(!has_common_type<hamon::tuple<int, int>, hamon::ranges::subrange<int*, int*>>(), "");
static_assert(!has_common_type<hamon::tuple<int*>, hamon::ranges::subrange<int*, int*>>(), "");

template <typename T, typename U, typename Expected>
constexpr bool test_common_type()
{
	return
		hamon::same_as_t<hamon::common_type_t<T, U>, Expected>::value &&
		hamon::same_as_t<hamon::common_type_t<U, T>, Expected>::value;
}

// Test common_type<tuple, tuple>
static_assert(test_common_type<hamon::tuple<>, hamon::tuple<>, hamon::tuple<>>(), "");
static_assert(test_common_type<hamon::tuple<char>, hamon::tuple<int>, hamon::tuple<int>>(), "");
static_assert(test_common_type<hamon::tuple<int&>, hamon::tuple<const int&>, hamon::tuple<int>>(), "");
static_assert(test_common_type<hamon::tuple<int&>, hamon::tuple<int&&>, hamon::tuple<int>>(), "");
static_assert(test_common_type<hamon::tuple<short, long, long>, hamon::tuple<long, int, short>, hamon::tuple<long, long, long>>(), "");

// Test common_reference<cvref tuple, cvref tuple>
static_assert(test_common_type<const hamon::tuple<>&, hamon::tuple<>&&, hamon::tuple<>>(), "");
static_assert(test_common_type<hamon::tuple<char>&, const hamon::tuple<int>&&, hamon::tuple<int>>(), "");
static_assert(test_common_type<hamon::tuple<int&>&, hamon::tuple<const int&>, hamon::tuple<int>>(), "");
static_assert(test_common_type<volatile hamon::tuple<int&>&, hamon::tuple<int&&>, hamon::tuple<int>>(), "");

// Test common_type<tuple, tuple-like>, tuple-like is pair
static_assert(test_common_type<hamon::tuple<int, int>, hamon::pair<int, int>, hamon::tuple<int, int>>(), "");
static_assert(test_common_type<hamon::tuple<int, long>, hamon::pair<short, long long>, hamon::tuple<int, long long>>(), "");
static_assert(test_common_type<hamon::tuple<int&, long&&>, hamon::pair<const int&, const long&&>, hamon::tuple<int, long>>(), "");
static_assert(test_common_type<hamon::tuple<short&, const volatile long&&>, hamon::pair<volatile int, long>, hamon::tuple<int, long>>(), "");

// Test common_type<cvref tuple, cvref tuple-like>, tuple-like is pair
static_assert(test_common_type<const hamon::tuple<int, int>&&, volatile hamon::pair<int, int>&, hamon::tuple<int, int>>(), "");
static_assert(test_common_type<volatile hamon::tuple<int, long>&&, const hamon::pair<short, long long>&&, hamon::tuple<int, long long>>(), "");

// Test common_type<tuple, tuple-like>, tuple-like is array
static_assert(test_common_type<hamon::tuple<>, hamon::array<int, 0>, hamon::tuple<>>(), "");
static_assert(test_common_type<hamon::tuple<int>, hamon::array<int, 1>, hamon::tuple<int>>(), "");
static_assert(test_common_type<hamon::tuple<int, long>, hamon::array<int, 2>, hamon::tuple<int, long>>(), "");
static_assert(test_common_type<hamon::tuple<short, int, long>, hamon::array<int, 3>, hamon::tuple<int, int, long>>(), "");
static_assert(test_common_type<hamon::tuple<short&, int&&, const volatile long>, hamon::array<int, 3>, hamon::tuple<int, int, long>>(), "");

// Test common_type<cvref tuple, cvref tuple-like>, tuple-like is array
static_assert(test_common_type<const hamon::tuple<>&&, volatile hamon::array<int, 0>&, hamon::tuple<>>(), "");
static_assert(test_common_type<const hamon::tuple<int>&, volatile hamon::array<int, 1>&&, hamon::tuple<int>>(), "");

// Test common_type<tuple, tuple-like>, tuple-like is ranges::subrange
static_assert(test_common_type<hamon::tuple<int*, int*>, hamon::ranges::subrange<int*, int*>, hamon::tuple<int*, int*>>(), "");
static_assert(test_common_type<hamon::tuple<int*, const int*>, hamon::ranges::subrange<const int*, int*>, hamon::tuple<const int*, const int*>>(), "");
//static_assert(test_common_type<hamon::tuple<int*, Sentinel>, hamon::ranges::subrange<int*, unreachable_sentinel_t>, hamon::tuple<int*, unreachable_sentinel_t>>(), "");
//static_assert(test_common_type<hamon::tuple<const volatile int*, Sentinel>, hamon::ranges::subrange<int*, unreachable_sentinel_t>, hamon::tuple<const volatile int*, unreachable_sentinel_t>>(), "");

// Test common_type<cvref tuple, cvref tuple-like>, tuple-like is ranges::subrange
static_assert(test_common_type<const hamon::tuple<int*, int*>&, volatile hamon::ranges::subrange<int*, int*>&&, hamon::tuple<int*, int*>>(), "");
//static_assert(test_common_type<volatile hamon::tuple<int*, Sentinel>&, const hamon::ranges::subrange<int*, unreachable_sentinel_t>&&, hamon::tuple<int*, unreachable_sentinel_t>>(), "");

}	// namespace common_type_test

}	// namespace hamon_tuple_test
