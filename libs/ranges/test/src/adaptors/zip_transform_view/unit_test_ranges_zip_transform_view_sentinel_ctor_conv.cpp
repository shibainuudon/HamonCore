/**
 *	@file	unit_test_ranges_zip_transform_view_sentinel_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr sentinel(sentinel<!Const> i)
 *    requires Const && convertible_to<zentinel<false>, zentinel<Const>>;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace sentinel_ctor_conv_test
{

struct Add
{
	constexpr int operator()(int x, char y) const { return x + y; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using F = Add;
	
	using V1 = test_input_view<int>;
	using V2 = test_input_view<int>;

	using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

	using S  = decltype(hamon::declval<ZV&>().end());
	using CS = decltype(hamon::declval<ZV const&>().end());
	//static_assert(hamon::is_same<S,  ZV::sentinel<false>>::value, "");
	//static_assert(hamon::is_same<CS, ZV::sentinel<true>>::value, "");
	static_assert(!hamon::is_same<S, CS>::value, "");

	static_assert(!hamon::is_constructible<S, CS>::value, "");
	static_assert( hamon::is_constructible<CS, S>::value, "");

	int a1[] = {42, 43, 44};
	int a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(Add{}, v1, v2);

	CS sent = zv.end();
	(void)sent;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewSentinelCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_conv_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
