/**
 *	@file	unit_test_unordered_multimap_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr bool operator==(
 *		const unordered_multimap<Key, T, Hash, Pred, Alloc>& a,
 *		const unordered_multimap<Key, T, Hash, Pred, Alloc>& b);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() == hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() != hamon::declval<Map const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>() == hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() != hamon::declval<Map const&>()), "");

	{
		Map v1;
		v1.emplace(Key{10}, T{42});
		v1.emplace(Key{20}, T{43});
		v1.emplace(Key{30}, T{44});
		v1.emplace(Key{30}, T{45});

		Map v2;
		v2.emplace(Key{30}, T{44});
		v2.emplace(Key{10}, T{42});
		v2.emplace(Key{30}, T{45});
		v2.emplace(Key{20}, T{43});

		VERIFY((v1 == v2) == true);
		VERIFY((v1 != v2) == false);

		v2.emplace(Key{30}, T{46});

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{10}, T{43} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{10}, T{43} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		VERIFY((v1 == v2) == true);
		VERIFY((v1 != v2) == false);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{10}, T{43} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{10}, T{43} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{10}, T{41} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}
	{
		Map const v1
		{
			{ Key{10}, T{42} },
			{ Key{10}, T{43} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		Map const v2
		{
			{ Key{10}, T{42} },
			{ Key{40}, T{43} },
			{ Key{20}, T{44} },
			{ Key{30}, T{45} },
		};

		VERIFY((v1 == v2) == false);
		VERIFY((v1 != v2) == true);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, OpCompareTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_unordered_multimap_test
