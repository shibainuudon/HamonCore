/**
 *	@file	unit_test_unordered_map_try_emplace_hint.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class... Args>
 *	constexpr iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args);
 *
 *	template<class... Args>
 *	constexpr iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_unordered_map_try_emplace) && (__cpp_lib_unordered_map_try_emplace >= 201411L))

namespace hamon_unordered_map_test
{

namespace try_emplace_hint_test
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
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key const&>(), hamon::declval<T const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key&&>(), hamon::declval<T const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key const&>(), hamon::declval<T const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key&&>(), hamon::declval<T const&>())), "");

	Map v;
	v.max_load_factor(0.25f);

	{
		auto r = v.try_emplace(v.end(), Key{1}, T{10});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
	}
	{
		auto r = v.try_emplace(v.begin(), Key{1}, T{20});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
	}
	{
		Key const k{2};
		auto r = v.try_emplace(v.cend(), k, T{20});
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{20});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
	}
	{
		Key const k{2};
		auto r = v.try_emplace(v.cbegin(), k, T{30});
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{20});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
	}
	{
		auto r = v.try_emplace(v.begin(), Key{3}, T{10});
		VERIFY(r->first == Key{3});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
		VERIFY(v[Key{3}] == T{10});
	}

	return true;
}

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}

	S1(S1&&)                 = delete;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;
};

UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	hamon::unordered_map<int, S1> v;
	v.max_load_factor(2.0f);

	{
		auto r = v.try_emplace(v.end(), 1, 10, 20);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.try_emplace(v.end(), 1, 30, 40);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.try_emplace(v.end(), 2, 50, 60);
		VERIFY(r->first == 2);
		VERIFY(r->second.x == 50);
		VERIFY(r->second.y == 60);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(2).x == 50);
		VERIFY(v.at(2).y == 60);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, TryEmplaceHintTest)
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

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::unordered_map<int, ThrowIfNegative> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.try_emplace(v.end(), 1, -1), ThrowIfNegative::Exception);
		EXPECT_EQ(0u, v.size());

		v.try_emplace(v.end(), 1, 10);
		EXPECT_EQ(1u, v.size());

		// 要素が挿入されないときは一時オブジェクトは作成されない
		EXPECT_NO_THROW(v.try_emplace(v.end(), 1, -1));
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.try_emplace(v.end(), 2, -10), ThrowIfNegative::Exception);
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.try_emplace(v.end(), 3, -20), ThrowIfNegative::Exception);
		EXPECT_EQ(1u, v.size());

		v.try_emplace(v.end(), 2, 11);
		EXPECT_EQ(2u, v.size());

		v.try_emplace(v.end(), 3, 12);
		EXPECT_EQ(3u, v.size());

		EXPECT_NO_THROW(v.try_emplace(v.end(), 2, -12));
		EXPECT_EQ(3u, v.size());

		EXPECT_NO_THROW(v.try_emplace(v.end(), 3, -20));
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace try_emplace_hint_test

}	// namespace hamon_unordered_map_test

#endif
