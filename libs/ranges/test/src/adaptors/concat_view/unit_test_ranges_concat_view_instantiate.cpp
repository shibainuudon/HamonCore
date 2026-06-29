/**
 *	@file	unit_test_ranges_concat_view_instantiate.cpp
 *
 *	@brief	concat_view のテスト
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace instantiate_test
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename... Ts>
struct CanInstantiateConcatViewImpl
{
private:
	template <typename... Us,
		typename = hamon::ranges::concat_view<Us...>>
	static auto test(int) -> hamon::true_type;

	template <typename... Us>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Ts...>(0));
};

template <typename... Ts>
using CanInstantiateConcatView = 
	typename CanInstantiateConcatViewImpl<Ts...>::type;

// sizeof...(Views) > 0
static_assert(!CanInstantiateConcatView<>::value, "");

// (view<Views> && ...)
static_assert(!CanInstantiateConcatView<test_input_range<int>>::value, "");
static_assert( CanInstantiateConcatView<test_input_view<int>>::value, "");
static_assert( CanInstantiateConcatView<test_input_view<int>,  test_input_view<int>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_range<int>, test_input_view<int>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_view<int>,  test_input_range<int>>::value, "");
static_assert( CanInstantiateConcatView<test_input_view<int>,  test_input_view<int>,  test_input_view<int>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_range<int>, test_input_view<int>,  test_input_view<int>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_view<int>,  test_input_range<int>, test_input_view<int>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_view<int>,  test_input_view<int>,  test_input_range<int>>::value, "");

struct A
{
};

struct B
{
	B(int){}
};

// concatable<Views...>
static_assert( CanInstantiateConcatView<test_input_view<int>, test_input_view<char>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_view<A>,   test_input_view<int>>::value, "");
static_assert(!CanInstantiateConcatView<test_input_view<int>, test_input_view<A>>::value, "");
static_assert( CanInstantiateConcatView<test_input_view<B>,   test_input_view<int>>::value, "");
static_assert( CanInstantiateConcatView<test_input_view<int>, test_input_view<B>>::value, "");

#endif

}	// namespace instantiate_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
