/**
 *	@file	unit_test_tuple_tuple_basic_common_reference.cpp
 *
 *	@brief	basic_common_referenceのテスト
 *
 *	template<tuple-like TTuple, tuple-like UTuple,
 *	         template<class> class TQual, template<class> class UQual>
 *	struct basic_common_reference<TTuple, UTuple, TQual, UQual> {
 *	  using type = see below;
 *	};
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/config.hpp>

namespace hamon_tuple_test
{

namespace basic_common_reference_test
{

template <typename T, typename = void>
struct has_type : hamon::false_type { };

template <typename T>
struct has_type<T, hamon::void_t<typename T::type>>: hamon::true_type { };

template <typename... T>
constexpr bool
has_common_ref()
{
	return has_type<hamon::common_reference<T...>>::value;
}

static_assert( has_common_ref<hamon::tuple<int>, int>(), "");
static_assert( has_common_ref<hamon::tuple<int>, float>(), "");
static_assert(!has_common_ref<hamon::tuple<int, int>, int>(), "");
static_assert(!has_common_ref<hamon::tuple<int*>, int>(), "");
static_assert( has_common_ref<int, hamon::tuple<int>>(), "");
static_assert( has_common_ref<int, hamon::tuple<float>>(), "");
static_assert( has_common_ref<hamon::tuple<int>, hamon::tuple<int>>(), "");
static_assert(!has_common_ref<hamon::tuple<int>, hamon::tuple<int, int>>(), "");
static_assert( has_common_ref<hamon::tuple<int, int>, hamon::tuple<int, int>>(), "");
static_assert( has_common_ref<hamon::tuple<int>, hamon::array<int, 1>>(), "");
static_assert(!has_common_ref<hamon::tuple<int>, hamon::array<int, 2>>(), "");
static_assert(!has_common_ref<hamon::tuple<int, int>, hamon::array<int, 1>>(), "");
static_assert( has_common_ref<hamon::tuple<int, int>, hamon::array<int, 2>>(), "");
static_assert(!has_common_ref<hamon::tuple<int>, hamon::pair<int, int>>(), "");
static_assert( has_common_ref<hamon::tuple<int, int>, hamon::pair<int, int>>(), "");

template <typename T, typename U, typename Expected>
constexpr bool test_common_reference()
{
	return
		hamon::same_as_t<hamon::common_reference_t<T, U>, Expected>::value &&
		hamon::same_as_t<hamon::common_reference_t<U, T>, Expected>::value;
}

static_assert(test_common_reference<int,   hamon::tuple<int>,   hamon::tuple<int>>(), "");
static_assert(test_common_reference<float, hamon::tuple<int>,   hamon::tuple<int>>(), "");
static_assert(test_common_reference<int,   hamon::tuple<float>, hamon::tuple<float>>(), "");

// Test common_reference<tuple, tuple>
static_assert(test_common_reference<hamon::tuple<>, hamon::tuple<>, hamon::tuple<>>(), "");
static_assert(test_common_reference<hamon::tuple<char&&>, hamon::tuple<const int&>, hamon::tuple<int>>(), "");
static_assert(test_common_reference<hamon::tuple<int&>, hamon::tuple<const int&>, hamon::tuple<const int&>>(), "");
static_assert(test_common_reference<hamon::tuple<int&>, hamon::tuple<int&&>, hamon::tuple<const int&>>(), "");
static_assert(test_common_reference<hamon::tuple<short, int, long>, hamon::tuple<long, int, short>, hamon::tuple<long, int, long>>(), "");

// Test common_reference<cvref tuple, cvref tuple>
static_assert(test_common_reference<hamon::tuple<>&, hamon::tuple<>&&, const hamon::tuple<>&>(), "");
static_assert(test_common_reference<const hamon::tuple<int, long>&, volatile hamon::tuple<int, long>&, const volatile hamon::tuple<int, long>&>(), "");
static_assert(test_common_reference<hamon::tuple<int&, const int&&, volatile int&>&, const hamon::tuple<const int&, const int, const int&>, hamon::tuple<const int&, int, const volatile int&>>(), "");

// Test common_reference<tuple, tuple-like>, tuple-like is pair
static_assert(test_common_reference<hamon::tuple<int, int>, hamon::pair<int, int>, hamon::tuple<int, int>>(), "");
static_assert(test_common_reference<hamon::tuple<int, long>, hamon::pair<short, long long>, hamon::tuple<int, long long>>(), "");
static_assert(test_common_reference<hamon::tuple<int&, long&&>, hamon::pair<const int&, const long&&>, hamon::tuple<const int&, const long&&>>(), "");
static_assert(test_common_reference<hamon::tuple<short&, const volatile long&&>, hamon::pair<volatile int, long>, hamon::tuple<int, long>>(), "");

// Test common_reference<cvref tuple, cvref tuple-like>, tuple-like is pair
static_assert(test_common_reference<hamon::tuple<int, int>&, hamon::pair<int, int>&, hamon::tuple<int&, int&>>(), "");
static_assert(test_common_reference<const hamon::tuple<int, int>&, const hamon::pair<int, int>&, hamon::tuple<const int&, const int&>>(), "");
static_assert(test_common_reference<hamon::tuple<int&, long&&>&, const hamon::pair<const int&, const long&&>&, hamon::tuple<const int&, const long&>>(), "");
static_assert(test_common_reference<const hamon::tuple<short&, const volatile long&&>, const hamon::pair<volatile int, long>&, hamon::tuple<int, long>>(), "");
static_assert(test_common_reference<const hamon::tuple<short&, const volatile long&>, const hamon::pair<volatile int, long>&, hamon::tuple<int, const volatile long&>>(), "");

// Test common_reference<tuple, tuple-like>, tuple-like is array
static_assert(test_common_reference<hamon::tuple<>, hamon::array<int, 0>, hamon::tuple<>>(), "");
static_assert(test_common_reference<hamon::tuple<int>, hamon::array<int, 1>, hamon::tuple<int>>(), "");
static_assert(test_common_reference<hamon::tuple<int, long>, hamon::array<int, 2>, hamon::tuple<int, long>>(), "");
static_assert(test_common_reference<hamon::tuple<short, int&&, const long>, hamon::array<int, 3>, hamon::tuple<int, int, long>>(), "");
static_assert(test_common_reference<hamon::tuple<short&, int&&, const volatile long>, hamon::array<int, 3>, hamon::tuple<int, int, long>>(), "");

// Test common_reference<cvref tuple, cvref tuple-like>, tuple-like is array
static_assert(test_common_reference<const hamon::tuple<>&, hamon::array<int, 0>, hamon::tuple<>>(), "");
static_assert(test_common_reference<hamon::tuple<int>&, hamon::array<int, 1>&, hamon::tuple<int&>>(), "");
static_assert(test_common_reference<const hamon::tuple<int, long>&&, hamon::array<int, 2>&, hamon::tuple<const int&, long>>(), "");

#if 0
// Test common_reference<tuple, tuple-like>, tuple-like is ranges::subrange
static_assert(test_common_reference<hamon::tuple<int*, int*>, subrange<int*, int*>, hamon::tuple<int*, int*>>(), "");
static_assert(test_common_reference<hamon::tuple<int*, const int*>, subrange<const int*, int*>, hamon::tuple<const int*, const int*>>(), "");
static_assert(test_common_reference<hamon::tuple<int*, Sentinel>, subrange<int*, unreachable_sentinel_t>, hamon::tuple<int*, unreachable_sentinel_t>>(), "");
static_assert(test_common_reference<hamon::tuple<const volatile int*, Sentinel>, subrange<int*, unreachable_sentinel_t>, hamon::tuple<const volatile int*, unreachable_sentinel_t>>(), "");

// Test common_reference<cvref tuple, cvref tuple-like>, tuple-like is ranges::subrange
static_assert(test_common_reference<const hamon::tuple<int*, int*>&&, const subrange<int*, int*>, hamon::tuple<int*, int*>>(), "");
static_assert(test_common_reference<const hamon::tuple<int*, const int*>&, subrange<const int*, int*>, hamon::tuple<const int*, const int*>>(), "");
#endif

}	// namespace basic_common_reference_test

}	// namespace hamon_tuple_test
