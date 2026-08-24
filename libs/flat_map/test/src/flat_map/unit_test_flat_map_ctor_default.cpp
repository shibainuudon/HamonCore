/**
 *	@file	unit_test_flat_map_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr flat_map();
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert( hamon::is_default_constructible<Map>::value, "");
	//static_assert( hamon::is_nothrow_default_constructible<Map>::value, "");
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

GTEST_TEST(FlatMapTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

}	// namespace ctor_default_test

}	// namespace hamon_flat_map_test
