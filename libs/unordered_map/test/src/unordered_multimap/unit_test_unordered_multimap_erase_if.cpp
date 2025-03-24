/**
 *	@file	unit_test_unordered_multimap_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class K, class T, class H, class P, class A, class Predicate>
 *	constexpr typename unordered_multimap<K, T, H, P, A>::size_type
 *	erase_if(unordered_multimap<K, T, H, P, A>& c, Predicate pred);
 */

#include <hamon/unordered_map/erase_if.hpp>
#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace erase_if_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct is_key_1
{
	template <typename T>
	constexpr bool operator()(T const& x) const
	{
		return x.first == 1;
	}
};

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using SizeType = typename Map::size_type;
	using ValueType = typename Map::value_type;

	static_assert(hamon::is_same<decltype(hamon::erase_if(hamon::declval<Map&>(), hamon::declval<is_key_1>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Map&>(), hamon::declval<is_key_1>())), "");

	{
		Map v
		{
			{ Key{1}, T{10} },
			{ Key{1}, T{20} },
			{ Key{2}, T{30} },
			{ Key{3}, T{40} },
			{ Key{3}, T{50} },
			{ Key{3}, T{60} },
		};

		auto r = hamon::erase_if(v, is_key_1{});
		VERIFY(r == 2);

		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		Map v
		{
			{ Key{1}, T{10} },
			{ Key{1}, T{20} },
			{ Key{2}, T{30} },
			{ Key{3}, T{40} },
			{ Key{3}, T{50} },
			{ Key{3}, T{60} },
		};

		auto r = hamon::erase_if(v, [](ValueType const& x){return x.first > 2;});
		VERIFY(r == 3);

		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		Map v
		{
			{ Key{1}, T{10} },
			{ Key{1}, T{20} },
			{ Key{2}, T{30} },
			{ Key{3}, T{40} },
			{ Key{3}, T{50} },
			{ Key{3}, T{60} },
		};

		auto r = hamon::erase_if(v, [](ValueType const& x){return x.second < 50;});
		VERIFY(r == 4);

		VERIFY(v.size() == 2);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 2);
		VERIFY(v.count(Key{4}) == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, EraseIfTest)
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

}	// namespace erase_if_test

}	// namespace hamon_unordered_multimap_test
