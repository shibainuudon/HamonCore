/**
 *	@file	unit_test_ranges_lazy_split_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const& requires copy_constructible<V>;
 *	constexpr V base() &&;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace base_test
{

template <typename T>
struct MoveOnlyView : hamon::ranges::view_base
{
	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
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
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
	
		static_assert( has_base<RV&>::value, "");
		static_assert( has_base<RV&&>::value, "");
		static_assert( has_base<RV const&>::value, "");
		static_assert( has_base<RV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<RV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV const&&>().base())>::value, "");
	}
	{
		using V = MoveOnlyView<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
	
		static_assert(!has_base<RV&>::value, "");
		static_assert( has_base<RV&&>::value, "");
		static_assert(!has_base<RV const&>::value, "");
		static_assert(!has_base<RV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<RV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<RV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<RV const&&>().base())>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using P = MoveOnlyView<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
	
		static_assert( has_base<RV&>::value, "");
		static_assert( has_base<RV&&>::value, "");
		static_assert( has_base<RV const&>::value, "");
		static_assert( has_base<RV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<RV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<RV const&&>().base())>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	{
		auto b = rv.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(rv).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace base_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
