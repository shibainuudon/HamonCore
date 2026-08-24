/**
 *	@file	unit_test_flat_map_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	constexpr void clear() noexcept;
 */

#include <hamon/flat_map/flat_map.hpp>
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
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().clear()), void>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().clear()), "");

	Map v
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
		{Key{1}, T{30}},
	};
	VERIFY(check_invariant(v));
	VERIFY(!v.empty());
	VERIFY(v.size() == 3);
	v.clear();
	VERIFY(check_invariant(v));
	VERIFY(v.empty());
	VERIFY(v.size() == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

}	// namespace clear_test

}	// namespace hamon_flat_map_test
