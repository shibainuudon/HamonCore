/**
 *	@file	unit_test_ranges_elements_view_adaptor.cpp
 *
 *	@brief	views::elements のテスト
 *
 *	hamon::views::elements
 *	hamon::views::keys
 *	hamon::views::values
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace adaptor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using Tuple = hamon::tuple<int, long>;
	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};

	using EV0 = hamon::ranges::elements_view<hamon::views::all_t<Tuple(&)[3]>, 0>;
	using EV1 = hamon::ranges::elements_view<hamon::views::all_t<Tuple(&)[3]>, 1>;

	// views::elements(v)
	{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
		auto ev = hamon::views::elements<0>(a);
#else
		auto ev = hamon::views::elements_t<0>{}(a);
#endif
		static_assert(hamon::is_same<decltype(ev), EV0>::value, "");
		int const expected[] = {1,3,5};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
		auto ev = hamon::views::elements<1>(a);
#else
		auto ev = hamon::views::elements_t<1>{}(a);
#endif
		static_assert(hamon::is_same<decltype(ev), EV1>::value, "");
		int const expected[] = {2,4,6};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = hamon::views::keys(a);
		static_assert(hamon::is_same<decltype(ev), EV0>::value, "");
		int const expected[] = {1,3,5};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = hamon::views::values(a);
		static_assert(hamon::is_same<decltype(ev), EV1>::value, "");
		int const expected[] = {2,4,6};
		VERIFY(hamon::ranges::equal(ev, expected));
	}

	// v | views::elements
	{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
		auto ev = a | hamon::views::elements<0>;
#else
		auto ev = a | hamon::views::elements_t<0>{};
#endif
		static_assert(hamon::is_same<decltype(ev), EV0>::value, "");
		int const expected[] = {1,3,5};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
		auto ev = a | hamon::views::elements<1>;
#else
		auto ev = a | hamon::views::elements_t<1>{};
#endif
		static_assert(hamon::is_same<decltype(ev), EV1>::value, "");
		int const expected[] = {2,4,6};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = a | hamon::views::keys;
		static_assert(hamon::is_same<decltype(ev), EV0>::value, "");
		int const expected[] = {1,3,5};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = a | hamon::views::values;
		static_assert(hamon::is_same<decltype(ev), EV1>::value, "");
		int const expected[] = {2,4,6};
		VERIFY(hamon::ranges::equal(ev, expected));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Tuple = hamon::tuple<int, long, short>;
	using V = test_forward_view<Tuple>;
	Tuple a[] =
	{
		Tuple{10, 11, 12},
		Tuple{20, 21, 22},
		Tuple{30, 31, 32},
		Tuple{40, 41, 42},
	};
	V v(a);

	using EV0 = hamon::ranges::elements_view<V, 0>;
	using EV1 = hamon::ranges::elements_view<V, 1>;
	using EV2 = hamon::ranges::elements_view<V, 2>;

	// views::elements(v)
	{
		auto ev = hamon::views::elements_t<0>{}(v);
		static_assert(hamon::is_same<decltype(ev), EV0>::value, "");
		int const expected[] = {10,20,30,40};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = hamon::views::elements_t<1>{}(v);
		static_assert(hamon::is_same<decltype(ev), EV1>::value, "");
		long const expected[] = {11,21,31,41};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = hamon::views::elements_t<2>{}(v);
		static_assert(hamon::is_same<decltype(ev), EV2>::value, "");
		short const expected[] = {12,22,32,42};
		VERIFY(hamon::ranges::equal(ev, expected));
	}

	// v | views::elements
	{
		auto ev = v | hamon::views::elements_t<0>{};
		static_assert(hamon::is_same<decltype(ev), EV0>::value, "");
		int const expected[] = {10,20,30,40};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = v | hamon::views::elements_t<1>{};
		static_assert(hamon::is_same<decltype(ev), EV1>::value, "");
		long const expected[] = {11,21,31,41};
		VERIFY(hamon::ranges::equal(ev, expected));
	}
	{
		auto ev = v | hamon::views::elements_t<2>{};
		static_assert(hamon::is_same<decltype(ev), EV2>::value, "");
		short const expected[] = {12,22,32,42};
		VERIFY(hamon::ranges::equal(ev, expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace adaptor_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
