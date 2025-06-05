/**
 *	@file	unit_test_flat_multimap_key_comp.cpp
 *
 *	@brief	key_comp のテスト
 *
 *	constexpr key_compare key_comp() const;
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

namespace key_comp_test
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
	using Compare = TestLess<Key>;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().key_comp()), Compare>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().key_comp()), Compare>::value, "");
	static_assert(!noexcept(hamon::declval<Map&      >().key_comp()), "");
	static_assert(!noexcept(hamon::declval<Map const&>().key_comp()), "");

	{
		Compare c1{4};
		Compare c2{5};
		Map v{c1};
		VERIFY(v.key_comp() == c1);
		VERIFY(v.key_comp() != c2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, KeyCompTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	{
		hamon::flat_multimap<int, char> m;
		auto comp = m.key_comp();

		EXPECT_TRUE (comp(1, 2));
		EXPECT_FALSE(comp(3, 2));
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace key_comp_test

}	// namespace hamon_flat_multimap_test
