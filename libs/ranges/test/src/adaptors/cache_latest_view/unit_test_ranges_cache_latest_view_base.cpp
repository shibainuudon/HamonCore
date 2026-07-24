/**
 *	@file	unit_test_ranges_cache_latest_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const & requires copy_constructible<V> { return base_; }
 *	constexpr V base() && { return std::move(base_); }
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
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
namespace cache_latest_view_test
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
		using CLV = hamon::ranges::cache_latest_view<V>;

		static_assert( has_base<CLV&>::value, "");
		static_assert( has_base<CLV&&>::value, "");
		static_assert( has_base<CLV const&>::value, "");
		static_assert( has_base<CLV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV const&&>().base())>::value, "");
	}
	{
		using V = MoveOnlyView<int>;
		using CLV = hamon::ranges::cache_latest_view<V>;

		static_assert(!has_base<CLV&>::value, "");
		static_assert( has_base<CLV&&>::value, "");
		static_assert(!has_base<CLV const&>::value, "");
		static_assert(!has_base<CLV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CLV const&&>().base())>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using CLV = hamon::ranges::cache_latest_view<V>;

	int a[] = {1,2,3};
	V v(a);
	CLV clv{v};
	{
		auto b = clv.base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	{
		auto b = hamon::move(clv).base();
		static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
		VERIFY(b.begin() == v.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace base_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
