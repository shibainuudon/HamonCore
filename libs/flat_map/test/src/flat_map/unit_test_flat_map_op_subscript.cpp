/**
 *	@file	unit_test_flat_map_op_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr mapped_type& operator[](const key_type& x);
 *	constexpr mapped_type& operator[](key_type&& x);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
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

namespace op_subscript_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<Key const&>()]), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<Key&&>()]),      T&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<Key const&>()]), "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<Key&&>()]), "");

	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
		};

		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{3}] == T{20});

		v[Key{2}] = T{30};

		VERIFY(v.size() == 3);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});

		{
			Key const k{1};
			v[k] = T{40};
		}

		VERIFY(v.size() == 3);
		VERIFY(v[Key{1}] == T{40});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});

		{
			Key const k{5};
			v[k] = T{50};
		}

		VERIFY(v.size() == 4);
		VERIFY(v[Key{1}] == T{40});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});
		VERIFY(v[Key{5}] == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, OpSubscriptTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace op_subscript_test

}	// namespace hamon_flat_map_test
