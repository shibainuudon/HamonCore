/**
 *	@file	unit_test_multimap_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	iterator  erase(iterator position);
 *	iterator  erase(const_iterator position);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace erase_position_test
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
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
#if !defined(HAMON_USE_STD_MULTIMAP)
	static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
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
		auto r = v.erase(hamon::next(v.begin(), 3));
		VERIFY(r == hamon::next(v.begin(), 3));
		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(hamon::next(v.cbegin(), 0));
		VERIFY(r == v.begin());
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(hamon::next(v.begin(), 1));
		VERIFY(r == hamon::next(v.begin(), 1));
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{40}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(hamon::next(v.cbegin(), 1));
		VERIFY(r == v.end());
		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{40}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(hamon::next(v.begin(), 0));
		VERIFY(r == v.end());
		VERIFY(v.size() == 0);
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

GTEST_TEST(MultimapTest, ErasePositionTest)
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

		v.erase(v.begin());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.erase(hamon::next(v.begin(), 1));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);
	}
	EXPECT_EQ(5, S::s_ctor_count);
	EXPECT_EQ(5, S::s_dtor_count);
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace erase_position_test

}	// namespace hamon_multimap_test
