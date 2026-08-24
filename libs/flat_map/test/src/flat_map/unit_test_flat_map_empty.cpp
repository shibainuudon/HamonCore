/**
 *	@file	unit_test_flat_map_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const noexcept;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().empty()), bool>::value, "");
	static_assert(noexcept(hamon::declval<Map&      >().empty()), "");
	static_assert(noexcept(hamon::declval<Map const&>().empty()), "");

	{
		Map v;
		VERIFY(v.empty() == true);
		v.insert({Key{42}, T{10}});
		VERIFY(v.empty() == false);
	}
	{
		Map const v;
		VERIFY(v.empty() == true);
	}
	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(v.empty() == false);
	}
	{
		Map const v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
			{Key{5}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(v.empty() == false);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));
}

}	// namespace empty_test

}	// namespace hamon_flat_map_test
