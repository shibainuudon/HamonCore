/**
 *	@file	unit_test_ranges_elements_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const & requires copy_constructible<V>;
 *	constexpr V base() &&;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace base_test
{

template <typename T>
struct MoveOnlyView : hamon::ranges::view_base
{
	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	T* begin() const noexcept;
	test_sentinel<T*> end() const noexcept;
};

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;

		static_assert( has_base<EV&>::value, "");
		static_assert( has_base<EV&&>::value, "");
		static_assert( has_base<EV const&>::value, "");
		static_assert( has_base<EV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&&>().base())>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 1>;

		static_assert( has_base<EV&>::value, "");
		static_assert( has_base<EV&&>::value, "");
		static_assert( has_base<EV const&>::value, "");
		static_assert( has_base<EV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&&>().base())>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = MoveOnlyView<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;

		static_assert(!has_base<EV&>::value, "");
		static_assert( has_base<EV&&>::value, "");
		static_assert(!has_base<EV const&>::value, "");
		static_assert(!has_base<EV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&&>().base())>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = MoveOnlyView<Tuple>;
		using EV = hamon::ranges::elements_view<V, 1>;

		static_assert(!has_base<EV&>::value, "");
		static_assert( has_base<EV&&>::value, "");
		static_assert(!has_base<EV const&>::value, "");
		static_assert(!has_base<EV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<EV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<EV const&&>().base())>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Tuple = hamon::tuple<int, long>;
	using V = test_input_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;

	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	EV ev{v};
	{
		auto b = ev.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(ev).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace base_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
