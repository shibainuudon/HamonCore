/**
 *	@file	unit_test_unordered_map_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr bool operator==(
 *		const unordered_map<Key, T, Hash, Pred, Alloc>& a,
 *		const unordered_map<Key, T, Hash, Pred, Alloc>& b);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() == hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() != hamon::declval<Map const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>() == hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() != hamon::declval<Map const&>()), "");

	{
		Map v1;
		v1.emplace(Key{10}, T{42});
		v1.emplace(Key{20}, T{43});
		v1.emplace(Key{30}, T{44});

		Map v2;
		v2.emplace(Key{30}, T{44});
		v2.emplace(Key{10}, T{42});
		v2.emplace(Key{20}, T{43});

		VERIFY((v1 == v2) == true);
		VERIFY((v1 != v2) == false);

		v2.emplace(Key{40}, T{45});

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{30}, T{44} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{30}, T{44} },
		};

		VERIFY((v1 == v2) == true);
		VERIFY((v1 != v2) == false);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{30}, T{44} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{30}, T{44} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{30}, T{42} },
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{30}, T{44} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{43} },
			{ Key{40}, T{44} },
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, OpCompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace op_compare_test

}	// namespace hamon_unordered_map_test
