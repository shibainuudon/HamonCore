/**
 *	@file	unit_test_flat_multimap_value_comp.cpp
 *
 *	@brief	value_comp のテスト
 *
 *	constexpr value_compare value_comp() const;
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace value_comp_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	{
		using Compare = hamon::less<Key>;
		using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
		using ValueCompare = typename Map::value_compare;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().value_comp()), ValueCompare>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().value_comp()), ValueCompare>::value, "");
		static_assert(!noexcept(hamon::declval<Map&      >().value_comp()), "");
		static_assert(!noexcept(hamon::declval<Map const&>().value_comp()), "");

		Map v;
		auto vc = v.value_comp();
		VERIFY( vc({Key{1}, T{2}}, {Key{2}, T{1}}));
		VERIFY(!vc({Key{1}, T{2}}, {Key{1}, T{3}}));
		VERIFY(!vc({Key{1}, T{2}}, {Key{1}, T{1}}));
		VERIFY(!vc({Key{2}, T{1}}, {Key{1}, T{2}}));
	}
	{
		using Compare = hamon::greater<Key>;
		using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
		using ValueCompare = typename Map::value_compare;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().value_comp()), ValueCompare>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().value_comp()), ValueCompare>::value, "");
		static_assert(!noexcept(hamon::declval<Map&      >().value_comp()), "");
		static_assert(!noexcept(hamon::declval<Map const&>().value_comp()), "");

		Map v;
		auto vc = v.value_comp();
		VERIFY(!vc({Key{1}, T{2}}, {Key{2}, T{1}}));
		VERIFY(!vc({Key{1}, T{2}}, {Key{1}, T{3}}));
		VERIFY(!vc({Key{1}, T{2}}, {Key{1}, T{1}}));
		VERIFY( vc({Key{2}, T{1}}, {Key{1}, T{2}}));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, ValueCompTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace value_comp_test

}	// namespace hamon_flat_multimap_test
