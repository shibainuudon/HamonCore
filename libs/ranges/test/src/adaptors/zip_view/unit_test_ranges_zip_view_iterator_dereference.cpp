/**
 *	@file	unit_test_ranges_zip_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr auto operator*() const;
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using ZV = hamon::ranges::zip_view<V>;
	using I = decltype(hamon::declval<ZV&>().begin());

	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), hamon::tuple<int&>>::value, "");

	int a[] = {42, 43, 44};
	V v(a);
	ZV zv(v);
	auto it = zv.begin();
	auto t = *it;
	VERIFY(hamon::adl_get<0>(t) == 42);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_input_view<int const>;
	using V2 = test_input_view<char>;
	using V3 = test_input_view<float>;
	using ZV = hamon::ranges::zip_view<V1, V2, V3>;
	using I = decltype(hamon::declval<ZV&>().begin());

	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), hamon::tuple<int const&, char&, float&>>::value, "");

	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	float a3[] = {0.5f, 1.5f, 2.5f};
	V1 v1(a1);
	V2 v2(a2);
	V3 v3(a3);
	ZV zv(v1, v2, v3);
	auto it = zv.begin();
	auto t = *it;
	VERIFY(hamon::adl_get<0>(t) == 42);
	VERIFY(hamon::adl_get<1>(t) == 1);
	VERIFY(hamon::adl_get<2>(t) == 0.5f);

	hamon::adl_get<1>(t) = 10;

	VERIFY(a2[0] == 10);
	VERIFY(a2[1] == 2);
	VERIFY(a2[2] == 3);
	VERIFY(a2[3] == 4);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_dereference_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
