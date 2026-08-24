/**
 *	@file	unit_test_flat_multimap_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const noexcept;
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

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using SizeType  = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Map&      >().size()), "");
	static_assert(noexcept(hamon::declval<Map const&>().size()), "");

	{
		Map v;
		VERIFY(v.size() == 0);
		v.insert({Key{1}, T{10}});
		VERIFY(v.size() == 1);
		v.insert({Key{2}, T{10}});
		VERIFY(v.size() == 2);
		v.insert({Key{2}, T{20}});
		VERIFY(v.size() == 3);
	}
	{
		Map const v;
		VERIFY(v.size() == 0);
	}
	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
		};
		VERIFY(v.size() == 5);
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
		VERIFY(v.size() == 6);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, SizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

}	// namespace size_test

}	// namespace hamon_flat_multimap_test
