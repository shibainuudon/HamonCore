/**
 *	@file	unit_test_multimap_erase_key.cpp
 *
 *	@brief	erase のテスト
 *
 *	size_type erase(const key_type& x);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace erase_key_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::multimap<Key, T>;
	using ValueType = typename Map::value_type;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_MULTIMAP)
	static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
#endif

	Map v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};
	VERIFY(v.size() == 5);

	{
		auto r = v.erase(Key{1});
		VERIFY(r == 2);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(Key{2});
		VERIFY(r == 0);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(Key{5});
		VERIFY(r == 1);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

struct S
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S()
	{
		++s_dtor_count;
	}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

GTEST_TEST(MultimapTest, EraseKeyTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::multimap<int, S> v;
		v.emplace(3, 10);
		v.emplace(1, 20);
		v.emplace(4, 30);
		v.emplace(2, 40);
		v.emplace(5, 50);
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		int const k{2};
		v.erase(k);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.erase(3);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);

		v.erase(k);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);

		v.erase(3);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(5, S::s_dtor_count);
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace erase_key_test

}	// namespace hamon_multimap_test
