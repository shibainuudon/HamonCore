/**
 *	@file	unit_test_ranges_zip_transform_view_adaptor.cpp
 *
 *	@brief	views::zip_transform のテスト
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <gtest/gtest.h>
#include <list>
#include <vector>
#include <string>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace adaptor_test
{

template <typename T>
struct F0
{
	T operator()() const;
};

struct F1
{
	template <typename T>
	constexpr T operator()(T x) const { return x * 2; }
};

struct F2
{
	template <typename T, typename U>
	constexpr auto operator()(T x, U y) const
	->decltype(x + y)
	{
		return x + y;
	}
};

struct F3
{
	template <typename... Args>
	void operator()(Args...) const;
};

// Microsoft-STLだと内部コンパイルエラーになってしまう
#if !defined(HAMON_USE_STD_RANGES_ZIP_TRANSFORM_VIEW) && defined(HAMON_STDLIB_DINKUMWARE)
using CPO = decltype(hamon::views::zip_transform);

static_assert( hamon::is_invocable<CPO, F0<int>>::value, "");
static_assert( hamon::is_invocable<CPO, F0<float>>::value, "");
static_assert(!hamon::is_invocable<CPO, F0<int>, int(&)[2]>::value, "");
static_assert(!hamon::is_invocable<CPO, F0<int>, int(&)[2], int(&)[3]>::value, "");

static_assert(!hamon::is_invocable<CPO, F1>::value, "");
static_assert( hamon::is_invocable<CPO, F1, int(&)[2]>::value, "");
static_assert( hamon::is_invocable<CPO, F1, float(&)[2]>::value, "");
static_assert(!hamon::is_invocable<CPO, F1, int(&)[2], int(&)[3]>::value, "");

static_assert(!hamon::is_invocable<CPO, F2>::value, "");
static_assert(!hamon::is_invocable<CPO, F2, int(&)[2]>::value, "");
static_assert( hamon::is_invocable<CPO, F2, int(&)[2], int(&)[3]>::value, "");
static_assert( hamon::is_invocable<CPO, F2, int(&)[2], float(&)[3]>::value, "");

static_assert(!hamon::is_invocable<CPO, F3>::value, "");
static_assert(!hamon::is_invocable<CPO, F3, int(&)[2]>::value, "");
static_assert(!hamon::is_invocable<CPO, F3, int(&)[2], int(&)[2]>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		auto zv = hamon::views::zip_transform(F0<int>{});
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::empty_view<int>>::value, "");
		VERIFY(zv.empty());
	}
	{
		auto zv = hamon::views::zip_transform(F0<float>{});
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::empty_view<float>>::value, "");
		VERIFY(zv.empty());
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int a[] = {1,2,3,4};
		auto zv = hamon::views::zip_transform(F1{}, a);
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::zip_transform_view<
				F1,
				hamon::views::all_t<int(&)[4]>
			>
		>::value, "");
		int const expected[] = {2,4,6,8};
		VERIFY(hamon::ranges::equal(zv, expected));
	}
	{
		float const a[] = {0.5f, 1.5f, 2.5f};
		auto zv = hamon::views::zip_transform(F1{}, a);
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::zip_transform_view<
				F1,
				hamon::views::all_t<float const(&)[3]>
			>
		>::value, "");
		float const expected[] = {1,3,5};
		VERIFY(hamon::ranges::equal(zv, expected));
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int a1[] = {1,2,3,4,5};
		char a2[] = {10,20,30};
		auto zv = hamon::views::zip_transform(F2{}, a1, a2);
		static_assert(hamon::is_same<decltype(zv),
			hamon::ranges::zip_transform_view<
				F2,
				hamon::views::all_t<int(&)[5]>,
				hamon::views::all_t<char(&)[3]>
			>
		>::value, "");
		int const expected[] = {11,22,33};
		VERIFY(hamon::ranges::equal(zv, expected));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());

	{
		std::vector<std::string> a1 =
		{
			"Alice",
			"Bob",
			"Charlie",
			"Dave",
		};
		std::list<std::string> a2 =
		{
			"The",
			"quick",
			"brown",
			"fox",
			"jumps",
			"over",
		};
		auto zv = hamon::views::zip_transform(F2{}, a1, a2);
		
		std::string const expected[] =
		{
			"AliceThe",
			"Bobquick",
			"Charliebrown",
			"Davefox",
		};
		EXPECT_TRUE(hamon::ranges::equal(zv, expected));
	}
}

}	// namespace adaptor_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
