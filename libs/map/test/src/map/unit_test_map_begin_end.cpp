/**
 *	@file	unit_test_map_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	iterator               begin() noexcept;
 *	const_iterator         begin() const noexcept;
 *	iterator               end() noexcept;
 *	const_iterator         end() const noexcept;
 *	const_iterator         cbegin() const noexcept;
 *	const_iterator         cend() const noexcept;
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	{
		Map v;
		Map const cv;
		static_assert(hamon::is_same<decltype(v.begin()),   Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.end()),     Iterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.begin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.end()),    ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cbegin()),  ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.cend()),    ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cbegin()), ConstIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.cend()),   ConstIterator>::value, "");

		static_assert(noexcept(v.begin()), "");
		static_assert(noexcept(v.end()), "");
		static_assert(noexcept(cv.begin()), "");
		static_assert(noexcept(cv.end()), "");
		static_assert(noexcept(v.cbegin()), "");
		static_assert(noexcept(v.cend()), "");
		static_assert(noexcept(cv.cbegin()), "");
		static_assert(noexcept(cv.cend()), "");
	}
	{
		Map v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Map const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Map v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{4}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
			{Key{2}, T{50}},
			{Key{1}, T{60}},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(it->first == 1);
		VERIFY(it->second == 10);
		VERIFY(*(++it) == ValueType{Key{2}, T{50}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == ValueType{Key{2}, T{50}});
		VERIFY(*it == ValueType{Key{4}, T{20}});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == ValueType{Key{4}, T{20}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == ValueType{Key{4}, T{20}});
		VERIFY(*it == ValueType{Key{2}, T{50}});
	}
	{
		Map const v
		{
			{Key{1}, T{10}},
			{Key{4}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
			{Key{2}, T{50}},
			{Key{1}, T{60}},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(it->first == 1);
		VERIFY(it->second == 10);
		VERIFY(*(++it) == ValueType{Key{2}, T{50}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == ValueType{Key{2}, T{50}});
		VERIFY(*it == ValueType{Key{4}, T{20}});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == ValueType{Key{4}, T{20}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == ValueType{Key{4}, T{20}});
		VERIFY(*it == ValueType{Key{2}, T{50}});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, BeginEndTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	// https://en.cppreference.com/w/cpp/container/map/begin
	{
		hamon::map<int, float> num_map;
		num_map[4] = 4.13f;
		num_map[9] = 9.24f;
		num_map[1] = 1.09f;

		auto it = num_map.begin();
		EXPECT_TRUE(it != num_map.end());
		EXPECT_EQ(1, it->first);
		EXPECT_EQ(1.09f, it->second);
		++it;
		EXPECT_TRUE(it != num_map.end());
		EXPECT_EQ(4, it->first);
		EXPECT_EQ(4.13f, it->second);
		++it;
		EXPECT_TRUE(it != num_map.end());
		EXPECT_EQ(9, it->first);
		EXPECT_EQ(9.24f, it->second);
		++it;
		EXPECT_TRUE(it == num_map.end());
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_map_test
