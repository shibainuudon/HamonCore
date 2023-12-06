/**
 *	@file	unit_test_pair_common_reference.cpp
 *
 *	@brief	common_reference のテスト
 */

#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/config.hpp>

namespace hamon_pair_test {
namespace common_reference_test {

struct X2 {};
struct Y2 {};
struct Z2 {};

}	// namespace common_reference_test
}	// namespace hamon_pair_test

namespace HAMON_COMMON_TYPE_NAMESPACE
{

template <>
struct common_type<
	hamon_pair_test::common_reference_test::X2,
	hamon_pair_test::common_reference_test::Y2>
{
	using type = hamon_pair_test::common_reference_test::Z2;
};

template <>
struct common_type<
	hamon_pair_test::common_reference_test::Y2,
	hamon_pair_test::common_reference_test::X2>
{
	using type = hamon_pair_test::common_reference_test::Z2;
};

}

namespace hamon_pair_test {
namespace common_reference_test {

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

static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<int, int>>(), "");
static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<int, int&>>(), "");
static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<int, int&&>>(), "");
static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<int, int const>>(), "");
static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<int, int const&>>(), "");
static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<int, int const&&>>(), "");
static_assert( has_common_ref<hamon::pair<int, int>, hamon::pair<long, short>>(), "");
static_assert(!has_common_ref<hamon::pair<int, int>, hamon::pair<int, int*>>(), "");
static_assert(!has_common_ref<hamon::pair<int, int>, hamon::pair<void*, int>>(), "");
static_assert(!has_common_ref<hamon::pair<int, X2>, hamon::pair<int, Z2>>(), "");
static_assert(!has_common_ref<hamon::pair<int, Y2>, hamon::pair<int, Z2>>(), "");

template <typename T, typename U, typename Expected>
constexpr bool test_common_reference()
{
	return
		hamon::same_as_t<hamon::common_reference_t<T, U>, Expected>::value &&
		hamon::same_as_t<hamon::common_reference_t<U, T>, Expected>::value;
}

static_assert(test_common_reference<hamon::pair<int, int>, hamon::pair<int, int>, hamon::pair<int, int>>(), "");
static_assert(test_common_reference<hamon::pair<int, long>, hamon::pair<long, int>, hamon::pair<long, long>>(), "");
static_assert(test_common_reference<hamon::pair<int&, const int&>, hamon::pair<const int&, int>, hamon::pair<const int&, int>>(), "");
static_assert(test_common_reference<hamon::pair<int&, volatile int&>, hamon::pair<volatile int&, int>, hamon::pair<volatile int&, int>>(), "");
static_assert(test_common_reference<hamon::pair<int&, const volatile int&>, hamon::pair<const volatile int&, int>, hamon::pair<const volatile int&, int>>(), "");
static_assert(test_common_reference<hamon::pair<int, X2>, hamon::pair<int, Y2>, hamon::pair<int, Z2>>(), "");

}	// namespace common_reference_test
}	// namespace hamon_pair_test
