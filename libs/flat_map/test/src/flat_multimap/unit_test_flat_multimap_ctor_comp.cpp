/**
 *	@file	unit_test_flat_multimap_ctor_comp.cpp
 *
 *	@brief	key_compare を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit flat_multimap(const key_compare& comp);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_comp_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert( hamon::is_constructible<Map, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Compare const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Compare const&>::value, "");

	{
		Compare const comp;
		Map v{comp};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}
	{
		TestLess<Key> const comp{42};
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{comp};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.key_comp() == comp);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, CtorCompTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

}	// namespace ctor_comp_test

}	// namespace hamon_flat_multimap_test
