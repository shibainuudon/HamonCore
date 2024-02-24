/**
 *	@file	unit_test_ranges_adjacent_view_adaptor.cpp
 *
 *	@brief	views::adjacent のテスト
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using AV = hamon::ranges::adjacent_view<V, 2>;

	int a[] = {1,2,3,4,5};
	V v(a);

	hamon::tuple<int, int> expected[] =
	{
		{1, 2},
		{2, 3},
		{3, 4},
		{4, 5},
	};

	// views::adjacent<N>(v)
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = hamon::views::adjacent<2>(v);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}
#endif
	{
		auto av = hamon::views::adjacent_t<2>{}(v);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// v | views::adjacent<N>
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = v | hamon::views::adjacent<2>;
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}
#endif
	{
		auto av = v | hamon::views::adjacent_t<2>{};
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// views::pairwise(v)
	{
		auto av = hamon::views::pairwise(v);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// v | views::pairwise
	{
		auto av = v | hamon::views::pairwise;
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using AV = hamon::ranges::adjacent_view<hamon::views::all_t<int(&)[5]>, 3>;

	int a[] = {1,2,3,4,5};

	hamon::tuple<int, int, int> expected[] =
	{
		{1, 2, 3},
		{2, 3, 4},
		{3, 4, 5},
	};

	// views::adjacent<N>(v)
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = hamon::views::adjacent<3>(a);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}
#endif
	{
		auto av = hamon::views::adjacent_t<3>{}(a);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	// v | views::adjacent<N>
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = a | hamon::views::adjacent<3>;
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}
#endif
	{
		auto av = a | hamon::views::adjacent_t<3>{};
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(hamon::ranges::equal(av, expected));
	}

	return true;
}

// N == 0
HAMON_CXX14_CONSTEXPR bool test02()
{
	using AV = hamon::ranges::empty_view<hamon::tuple<>>;

	int a[] = {1,2,3,4,5};

	// views::adjacent<N>(v)
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = hamon::views::adjacent<0>(a);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}
#endif
	{
		auto av = hamon::views::adjacent_t<0>{}(a);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}

	// v | views::adjacent<N>
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = a | hamon::views::adjacent<0>;
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}
#endif
	{
		auto av = a | hamon::views::adjacent_t<0>{};
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}

	return true;
}

// N > ranges::size(v)
HAMON_CXX14_CONSTEXPR bool test03()
{
	using AV = hamon::ranges::adjacent_view<hamon::views::all_t<int(&)[3]>, 4>;

	int a[] = {1,2,3};

	// views::adjacent<N>(v)
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = hamon::views::adjacent<4>(a);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}
#endif
	{
		auto av = hamon::views::adjacent_t<4>{}(a);
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}

	// v | views::adjacent<N>
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	{
		auto av = a | hamon::views::adjacent<4>;
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}
#endif
	{
		auto av = a | hamon::views::adjacent_t<4>{};
		static_assert(hamon::is_same<decltype(av), AV>::value, "");
		VERIFY(av.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace adaptor_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
