/**
 *	@file	unit_test_ranges_as_input_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const & requires copy_constructible<V> { return base_; }
 *	constexpr V base() && { return std::move(base_); }
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using AIV = hamon::ranges::as_input_view<V>;

		static_assert( has_base<AIV&>::value, "");
		static_assert( has_base<AIV&&>::value, "");
		static_assert( has_base<AIV const&>::value, "");
		static_assert( has_base<AIV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV const&&>().base())>::value, "");
	}
	{
		using V = MoveOnlyView<int>;
		using AIV = hamon::ranges::as_input_view<V>;

		static_assert(!has_base<AIV&>::value, "");
		static_assert( has_base<AIV&&>::value, "");
		static_assert(!has_base<AIV const&>::value, "");
		static_assert(!has_base<AIV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<AIV const&&>().base())>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using AIV = hamon::ranges::as_input_view<V>;

	int a[] = {1,2,3};
	V v(a);
	AIV aiv{v};
	{
		auto b = aiv.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(aiv).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace base_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
