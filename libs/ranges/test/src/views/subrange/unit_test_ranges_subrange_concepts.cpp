/**
 *	@file	unit_test_ranges_subrange_concepts.cpp
 *
 *	@brief	ranges::subrange に関係するコンセプトのテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace concepts_test
{

template <typename... Args>
struct ValidSubrangeImpl
{
private:
	template <typename... Args2,
		typename = hamon::ranges::subrange<Args2...>
	>
	static auto test(int) -> hamon::true_type;

	template <typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Args...>(0));
};

template <typename... Args>
using ValidSubrange = typename ValidSubrangeImpl<Args...>::type;

template <hamon::ranges::subrange_kind K, typename... Args>
struct ValidSubrangeKindImpl
{
private:
	template <hamon::ranges::subrange_kind K2, typename... Args2,
		typename = hamon::ranges::subrange<Args2..., K2>
	>
	static auto test(int) -> hamon::true_type;

	template <hamon::ranges::subrange_kind K2, typename... Args2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<K, Args...>(0));
};

template <hamon::ranges::subrange_kind K, typename... Args>
using ValidSubrangeKind = typename ValidSubrangeKindImpl<K, Args...>::type;

static_assert( ValidSubrange<forward_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrange<forward_iterator_wrapper<int>, forward_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrange<forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>::value, "");
static_assert( ValidSubrangeKind<hamon::ranges::subrange_kind::unsized, forward_iterator_wrapper<int>, forward_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrangeKind<hamon::ranges::subrange_kind::sized,   forward_iterator_wrapper<int>, forward_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrange<random_access_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrange<random_access_iterator_wrapper<int>, random_access_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrange<random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>::value, "");
// Wrong sentinel type.
static_assert(!ValidSubrange<forward_iterator_wrapper<int>, int*>::value, "");
static_assert(!ValidSubrange<int*, forward_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrange<int*>::value, "");
static_assert( ValidSubrange<int*, int*>::value, "");
// Must be sized.
static_assert(!ValidSubrangeKind<hamon::ranges::subrange_kind::unsized, int*, int*>::value, "");
static_assert( ValidSubrangeKind<hamon::ranges::subrange_kind::sized,   int*, int*>::value, "");
static_assert(!ValidSubrangeKind<hamon::ranges::subrange_kind::unsized, random_access_iterator_wrapper<int>, random_access_iterator_wrapper<int>>::value, "");
static_assert( ValidSubrangeKind<hamon::ranges::subrange_kind::sized,   random_access_iterator_wrapper<int>, random_access_iterator_wrapper<int>>::value, "");
static_assert(!ValidSubrangeKind<hamon::ranges::subrange_kind::unsized, random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>::value, "");
static_assert( ValidSubrangeKind<hamon::ranges::subrange_kind::sized,   random_access_iterator_wrapper<int>, test_sentinel<random_access_iterator_wrapper<int>>>::value, "");
// Not an iterator.
static_assert(!ValidSubrange<int>::value, "");
static_assert(!ValidSubrange<int&>::value, "");

static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::subrange<int*>>::value, "");
static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::subrange<forward_iterator_wrapper<int>>>::value, "");
static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::subrange<forward_iterator_wrapper<int>, test_sentinel<forward_iterator_wrapper<int>>>>::value, "");
static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::subrange<int*, const int*, hamon::ranges::subrange_kind::sized>>::value, "");
static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::subrange<int*, hamon::unreachable_sentinel_t, hamon::ranges::subrange_kind::sized>>::value, "");
static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::subrange<int*, hamon::unreachable_sentinel_t, hamon::ranges::subrange_kind::unsized>>::value, "");

static_assert(hamon::detail::is_specialization_of_subrange<hamon::ranges::subrange<int*, int*, hamon::ranges::subrange_kind::sized>>::value, "");

}	// namespace concepts_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
