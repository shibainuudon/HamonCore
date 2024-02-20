/**
 *	@file	unit_test_ranges_zip_transform_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr decltype(auto) operator*() const noexcept(see below);
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace iterator_dereference_test
{

struct F1
{
	constexpr int& operator()(int& x) const { return x; }
	constexpr int const& operator()(int const& x) const { return x; }
};

struct F2
{
	int operator()(int&) const;
	int operator()(int const&) const;
};

struct F3
{
	char  operator()(int) const;
	float operator()(int, int) const;
	long  operator()(int, int, int) const;
};

struct Add
{
	constexpr float operator()(int x, float y) const { return float(x) + y; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int&>::value, "");
	}
	{
		using V = test_input_view<int const>;
		using ZV = hamon::ranges::zip_transform_view<F1, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int const&>::value, "");
	}
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F2, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int>::value, "");
	}
	{
		using V = test_input_view<int const>;
		using ZV = hamon::ranges::zip_transform_view<F2, V>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F3, V1>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), char>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F3, V1, V1>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), float>::value, "");
	}
	{
		using V1 = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F3, V1, V1, V1>;
		using I = decltype(hamon::declval<ZV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), long>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<float>;
	using ZV = hamon::ranges::zip_transform_view<Add, V1, V2>;

	Add f{};
	int a1[] = {3,1,4,1,5};
	float a2[] = {0.5f, 1.5f, 2.5f};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(f, v1, v2);
	auto it = zv.begin();
	VERIFY(*it == 3.5f);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = test_input_view<int>;
	using ZV = hamon::ranges::zip_transform_view<F1, V1>;

	F1 f{};
	int a1[] = {3,1,4,1,5};
	V1 v1(a1);
	ZV zv(f, v1);
	auto it = zv.begin();
	VERIFY(*it == 3);

	*it = 42;

	VERIFY(a1[0] == 42);
	VERIFY(a1[1] == 1);
	VERIFY(a1[2] == 4);
	VERIFY(a1[3] == 1);
	VERIFY(a1[4] == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_dereference_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
