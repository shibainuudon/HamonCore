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

static_assert( has_common_ref<hamon::tuple<int>, hamon::tuple<int>>(), "");
static_assert(!has_common_ref<hamon::tuple<int>, hamon::tuple<int, int>>(), "");
static_assert( has_common_ref<hamon::tuple<int, int>, hamon::tuple<int, int>>(), "");
static_assert( has_common_ref<hamon::tuple<int>, hamon::array<int, 1>>(), "");
static_assert(!has_common_ref<hamon::tuple<int>, hamon::array<int, 2>>(), "");
static_assert(!has_common_ref<hamon::tuple<int, int>, hamon::array<int, 1>>(), "");
static_assert( has_common_ref<hamon::tuple<int, int>, hamon::array<int, 2>>(), "");
static_assert(!has_common_ref<hamon::tuple<int>, hamon::pair<int, int>>(), "");
static_assert( has_common_ref<hamon::tuple<int, int>, hamon::pair<int, int>>(), "");

template <typename Expected, typename T, typename U>
constexpr bool
test_common_reference()
{
	return
		hamon::is_same<Expected, hamon::common_reference_t<T, U>>::value &&
		hamon::is_same<Expected, hamon::common_reference_t<U, T>>::value;
}

static_assert(test_common_reference<hamon::tuple<>, hamon::tuple<>, hamon::tuple<>>(), "");
static_assert(test_common_reference<hamon::tuple<int>, hamon::tuple<char&&>, hamon::tuple<int const&>>(), "");
static_assert(test_common_reference<hamon::tuple<int const&>, hamon::tuple<int&>, hamon::tuple<int const&>>(), "");
static_assert(test_common_reference<hamon::tuple<int const&>, hamon::tuple<int&>, hamon::tuple<int&&>>(), "");
static_assert(test_common_reference<hamon::tuple<long, int, long>, hamon::tuple<short, int, long>, hamon::tuple<long, int, short>>(), "");

static_assert(test_common_reference<hamon::tuple<>, hamon::tuple<> const, hamon::tuple<>>(), "");
static_assert(test_common_reference<hamon::tuple<>, hamon::tuple<>,       hamon::tuple<> const>(), "");
static_assert(test_common_reference<hamon::tuple<>, hamon::tuple<> const, hamon::tuple<> const>(), "");

static_assert(test_common_reference<hamon::tuple<> &,      hamon::tuple<> &,      hamon::tuple<>&>(), "");
static_assert(test_common_reference<hamon::tuple<> const&, hamon::tuple<> const&, hamon::tuple<>&>(), "");
static_assert(test_common_reference<hamon::tuple<> const&, hamon::tuple<> &,      hamon::tuple<> const&>(), "");
static_assert(test_common_reference<hamon::tuple<> const&, hamon::tuple<> const&, hamon::tuple<> const&>(), "");

}	// namespace basic_common_reference_test

}	// namespace hamon_tuple_test
