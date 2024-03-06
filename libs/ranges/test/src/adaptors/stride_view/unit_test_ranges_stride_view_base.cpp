/**
 *	@file	unit_test_ranges_stride_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const & requires copy_constructible<V> { return base_; }
 *	constexpr V base() && { return std::move(base_); }
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
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
namespace stride_view_test
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
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;

		static_assert( has_base<SV&>::value, "");
		static_assert( has_base<SV&&>::value, "");
		static_assert( has_base<SV const&>::value, "");
		static_assert( has_base<SV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<SV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<SV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<SV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<SV const&&>().base())>::value, "");
	}
	{
		using V = MoveOnlyView<int>;
		using SV = hamon::ranges::stride_view<V>;

		static_assert(!has_base<SV&>::value, "");
		static_assert( has_base<SV&&>::value, "");
		static_assert(!has_base<SV const&>::value, "");
		static_assert(!has_base<SV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<SV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<SV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<SV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<SV const&&>().base())>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {1,2,3};
	V v(a);
	SV sv{v, 2};
	{
		auto b = sv.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(sv).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace base_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
