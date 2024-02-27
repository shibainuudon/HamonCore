/**
 *	@file	unit_test_ranges_adjacent_transform_view_adaptor.cpp
 *
 *	@brief	views::adjacent_transform のテスト
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
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

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
	constexpr int operator()(int x, int y, int z) const { return x + y + z; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[] = {1,2,3,4,5};
	test_forward_view<int> v(a);

	{
		auto av = hamon::views::adjacent_transform<0>(v, F0<int>{});
		static_assert(hamon::is_same<decltype(av),
			hamon::ranges::empty_view<int>>::value, "");
		VERIFY(av.empty());
	}

	{
		auto av = v | hamon::views::adjacent_transform<0>(F0<float>{});
		static_assert(hamon::is_same<decltype(av),
			hamon::ranges::empty_view<float>>::value, "");
		VERIFY(av.empty());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using AV = hamon::ranges::adjacent_transform_view<V, Add, 2>;

	int a[] = {1,2,3,4,5};
	V v(a);

	int expected[] = {3,5,7,9};

	// views::adjacent_transform<N>(v, f)
	{
		auto av = hamon::views::adjacent_transform<2>(v, Add{});
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// v | views::adjacent_transform<N>(f)
	{
		auto av = v | hamon::views::adjacent_transform<2>(Add{});
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// views::pairwise_transform(v, f)
	{
		auto av = hamon::views::pairwise_transform(v, Add{});
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// v | views::pairwise_transform(f)
	{
		auto av = v | hamon::views::pairwise_transform(Add{});
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using AV = hamon::ranges::adjacent_transform_view<hamon::views::all_t<int(&)[5]>, Add, 3>;

	int a[] = {1,2,3,4,5};

	int expected[] = {6,9,12};

	// views::adjacent_transform<N>(v, f)
	{
		auto av = hamon::views::adjacent_transform<3>(a, Add{});
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// v | views::adjacent_transform<N>(f)
	{
		auto av = a | hamon::views::adjacent_transform<3>(Add{});
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		using CPO = decltype(hamon::views::adjacent_transform<0>);
		static_assert( hamon::is_invocable<CPO, int(&)[3], F0<int>>::value, "");
		static_assert(!hamon::is_invocable<CPO, int(&)[3], F1>::value, "");
		static_assert(!hamon::is_invocable<CPO, int(&)[3], Add>::value, "");
	}
	{
		using CPO = decltype(hamon::views::adjacent_transform<1>);
		static_assert(!hamon::is_invocable<CPO, int(&)[3], F0<int>>::value, "");
		static_assert( hamon::is_invocable<CPO, int(&)[3], F1>::value, "");
		static_assert(!hamon::is_invocable<CPO, int(&)[3], Add>::value, "");
	}
	{
		using CPO = decltype(hamon::views::adjacent_transform<2>);
		static_assert(!hamon::is_invocable<CPO, int(&)[3], F0<int>>::value, "");
		static_assert(!hamon::is_invocable<CPO, int(&)[3], F1>::value, "");
		static_assert( hamon::is_invocable<CPO, int(&)[3], Add>::value, "");
	}
	{
		using CPO = decltype(hamon::views::adjacent_transform<3>);
		static_assert(!hamon::is_invocable<CPO, int(&)[3], F0<int>>::value, "");
		static_assert(!hamon::is_invocable<CPO, int(&)[3], F1>::value, "");
		static_assert( hamon::is_invocable<CPO, int(&)[3], Add>::value, "");
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace adaptor_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
