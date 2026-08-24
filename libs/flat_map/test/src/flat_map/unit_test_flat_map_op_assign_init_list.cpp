/**
 *	@file	unit_test_flat_map_op_assign_init_list.cpp
 *
 *	@brief	operator= のテスト
 *
 *	constexpr flat_map& operator=(initializer_list<value_type>);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace op_assign_init_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().operator=(hamon::declval<hamon::initializer_list<ValueType>>())), Map&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().operator=(hamon::declval<hamon::initializer_list<ValueType>>())), "");

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{3}] == T{20});

	{
		auto& r = (v = {
			{Key{2}, T{30}},
			{Key{1}, T{40}},
			{Key{4}, T{50}},
		});
		VERIFY(&r == &v);
	}

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{40});
	VERIFY(v[Key{2}] == T{30});
	VERIFY(v[Key{4}] == T{50});

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, OpAssignInitListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	{
		hamon::flat_map<hamon::string, int> fm;
		EXPECT_TRUE(fm.empty());

		fm =
		{
			{hamon::string("Carol"), 4},
			{hamon::string("Alice"), 3},
			{hamon::string("Bob"),   1},
		};

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":" << p.second  << ", ";
		}
		EXPECT_EQ("Alice:3, Bob:1, Carol:4, ", ss.str());
	}
}

}	// namespace op_assign_init_list_test

}	// namespace hamon_flat_map_test
