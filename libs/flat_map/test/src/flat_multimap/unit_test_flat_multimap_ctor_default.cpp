/**
 *	@file	unit_test_flat_multimap_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr flat_multimap();
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_default_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::flat_multimap<Key, T>;

	static_assert( hamon::is_default_constructible<Map>::value, "");
#if !defined(HAMON_USE_STD_FLAT_MAP)
	//static_assert(!hamon::is_nothrow_default_constructible<Map>::value, "");
#endif
	static_assert( hamon::is_implicitly_default_constructible<Map>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Map>::value, "");

	{
		Map v;
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}
	{
		Map v{};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}
	{
		Map v = {};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, CtorDefaultTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_default_test

}	// namespace hamon_flat_multimap_test
