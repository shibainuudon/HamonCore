/**
 *	@file	unit_test_flat_map_key_comp.cpp
 *
 *	@brief	key_comp のテスト
 *
 *	constexpr key_compare key_comp() const;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace key_comp_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Compare = TestLess<Key>;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;

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

GTEST_TEST(FlatMapTest, KeyCompTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	{
		hamon::flat_map<int, char> m;
		auto comp = m.key_comp();

		EXPECT_TRUE (comp(1, 2));
		EXPECT_FALSE(comp(3, 2));
	}
}

}	// namespace key_comp_test

}	// namespace hamon_flat_map_test
