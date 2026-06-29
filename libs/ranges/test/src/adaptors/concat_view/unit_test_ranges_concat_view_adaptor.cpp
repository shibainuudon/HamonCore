/**
 *	@file	unit_test_ranges_concat_view_adaptor.cpp
 *
 *	@brief	views::concat のテスト
 *
 *	views::concat
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/adaptors/owning_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;

	int a[] = {1,2,3};
	V v(a);
	auto cv = hamon::views::concat(v);
	static_assert(hamon::is_same<decltype(cv), V>::value, "");

	const int expected[] = {1,2,3};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1,2,3};
	auto cv = hamon::views::concat(a);
	static_assert(hamon::is_same<decltype(cv), hamon::ranges::ref_view<int[3]>>::value, "");

	const int expected[] = {1,2,3};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a1[] = {1,2,3};
	int const a2[] = {4,5};
	auto cv = hamon::views::concat(a1, a2);
	static_assert(hamon::is_same<decltype(cv),
		hamon::ranges::concat_view<
			hamon::ranges::ref_view<int[3]>,
			hamon::ranges::ref_view<int const[2]>
		>>::value, "");

	const int expected[] = {1,2,3,4,5};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<float>;
	using V3 = test_random_access_view<char>;

	int a1[] = {1};
	float a2[] = {2,3};
	char a3[] = {4,5,6};

	V1 v1(a1);
	V2 v2(a2);
	V3 v3(a3);

	auto cv = hamon::views::concat(v1, v2, v3);
	static_assert(hamon::is_same<decltype(cv),
		hamon::ranges::concat_view<V1, V2, V3>>::value, "");

	const float expected[] = {1,2,3,4,5,6};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX20_CONSTEXPR bool test04()
{
	hamon::vector<int> v1{ 1, 2, 3 };
	hamon::vector<int> v2{ 4, 5 };
	hamon::array<int, 3> a{ 6, 7, 8 };

	auto cv = hamon::views::concat(v1, v2, a);
	static_assert(hamon::is_same<
		decltype(cv),
		hamon::ranges::concat_view<
		hamon::ranges::ref_view<hamon::vector<int>>,
		hamon::ranges::ref_view<hamon::vector<int>>,
		hamon::ranges::ref_view<hamon::array<int, 3>>
		>
	>::value, "");

	const int expected[] = {1,2,3,4,5,6,7,8};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

HAMON_CXX20_CONSTEXPR bool test05()
{
	auto cv = hamon::views::concat(
		hamon::vector<int>{1, 2, 3},
		hamon::vector<int>{4, 5},
		hamon::array<int, 3>{6, 7, 8});
	static_assert(hamon::is_same<
		decltype(cv),
		hamon::ranges::concat_view<
		hamon::ranges::owning_view<hamon::vector<int>>,
		hamon::ranges::owning_view<hamon::vector<int>>,
		hamon::ranges::owning_view<hamon::array<int, 3>>
		>
	>::value, "");

	const int expected[] = {1,2,3,4,5,6,7,8};
	VERIFY(hamon::ranges::equal(cv, expected));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace adaptor_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
