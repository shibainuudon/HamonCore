/**
 *	@file	unit_test_ranges_chunk_by_view_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr V base() const & requires copy_constructible<V> { return base_; }
 *	constexpr V base() && { return std::move(base_); }
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/functional/ranges/less.hpp>
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
namespace chunk_by_view_test
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
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;

		static_assert( has_base<CV&>::value, "");
		static_assert( has_base<CV&&>::value, "");
		static_assert( has_base<CV const&>::value, "");
		static_assert( has_base<CV const&&>::value, "");

		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&&>().base())>::value, "");

		int a[] = {1,2,3};
		V v(a);
		CV cv(v, F{});
		{
			auto b = cv.base();
			static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
			VERIFY(b.begin() == v.begin());
		}
		{
			auto b = hamon::move(cv).base();
			static_assert(hamon::is_same<decltype(b), decltype(v)>::value, "");
			VERIFY(b.begin() == v.begin());
		}
	}
	{
		using V = MoveOnlyView<int>;
		using F = hamon::ranges::less;
		using CV = hamon::ranges::chunk_by_view<V, F>;

		static_assert(!has_base<CV&>::value, "");
		static_assert( has_base<CV&&>::value, "");
		static_assert(!has_base<CV const&>::value, "");
		static_assert(!has_base<CV const&&>::value, "");

//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&>().base())>::value, "");
		static_assert(hamon::is_same<V, decltype(hamon::declval<CV&&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&>().base())>::value, "");
//		static_assert(hamon::is_same<V, decltype(hamon::declval<CV const&&>().base())>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace base_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
