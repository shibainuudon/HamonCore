/**
 *	@file	unit_test_unordered_map_op_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr mapped_type& operator[](const key_type& k);
 *	constexpr mapped_type& operator[](key_type&& k);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace op_subscript_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using MappedType = typename Map::mapped_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<Key const&>()]), MappedType&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<Key&&>()]), MappedType&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<Key const&>()]), "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<Key&&>()]), "");

	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
		};

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{3}] == T{20});

		v[Key{2}] = T{30};

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});

		{
			Key const k{1};
			v[k] = T{40};
		}

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{40});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});

		for (int i = 0; i < 100; ++i)
		{
			v[static_cast<Key>(i)] = T{42};
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, OpSubscriptTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace op_subscript_test

}	// namespace hamon_unordered_map_test
