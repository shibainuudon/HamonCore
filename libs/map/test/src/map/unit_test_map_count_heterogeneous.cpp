/**
 *	@file	unit_test_map_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K> size_type count(const K& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

namespace hamon_map_test
{

namespace count_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S
{
	int value;

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

// template<class K> size_type count(const K& x) const;
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<S, float, hamon::less<>>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<int const&>())), "");

	Map const v
	{
		{S{8}, 13.5f},
		{S{2}, 10.5f},
		{S{5}, 11.5f},
		{S{8}, 13.5f},
		{S{5}, 11.5f},
		{S{6}, 12.5f},
		{S{8}, 13.5f},
	};

	VERIFY(v.count(0) == 0);
	VERIFY(v.count(1) == 0);
	VERIFY(v.count(2) == 1);
	VERIFY(v.count(3) == 0);
	VERIFY(v.count(4) == 0);
	VERIFY(v.count(5) == 1);
	VERIFY(v.count(6) == 1);
	VERIFY(v.count(7) == 0);
	VERIFY(v.count(8) == 1);
	VERIFY(v.count(9) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, CountHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_map_test

#endif
