/**
 *	@file	unit_test_map_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	reverse_iterator       rbegin() noexcept;
 *	const_reverse_iterator rbegin() const noexcept;
 *	reverse_iterator       rend() noexcept;
 *	const_reverse_iterator rend() const noexcept;
 *	const_reverse_iterator crbegin() const noexcept;
 *	const_reverse_iterator crend() const noexcept;
 */

#include <hamon/map/map.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace rbegin_rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using ReverseIterator = typename Map::reverse_iterator;
	using ConstReverseIterator = typename Map::const_reverse_iterator;

	{
		Map v;
		Map const cv;
		static_assert(hamon::is_same<decltype(v.rbegin()),   ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.rend()),     ReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.rend()),    ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.crbegin()),  ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(v.crend()),    ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crbegin()), ConstReverseIterator>::value, "");
		static_assert(hamon::is_same<decltype(cv.crend()),   ConstReverseIterator>::value, "");

		static_assert(noexcept(v.rbegin()), "");
		static_assert(noexcept(v.rend()), "");
		static_assert(noexcept(cv.rbegin()), "");
		static_assert(noexcept(cv.rend()), "");
		static_assert(noexcept(v.crbegin()), "");
		static_assert(noexcept(v.crend()), "");
		static_assert(noexcept(cv.crbegin()), "");
		static_assert(noexcept(cv.crend()), "");
	}
	{
		Map v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Map const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Map v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
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
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(it->first == 4);
		VERIFY(it->second == 20);
		VERIFY(*(++it) == ValueType{Key{2}, T{50}});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == ValueType{Key{2}, T{50}});
		VERIFY(*it == ValueType{Key{1}, T{10}});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(*(--it) == ValueType{Key{1}, T{10}});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it--) == ValueType{Key{1}, T{10}});
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
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(it->first == 4);
		VERIFY(it->second == 20);
		VERIFY(*(++it) == ValueType{Key{2}, T{50}});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == ValueType{Key{2}, T{50}});
		VERIFY(*it == ValueType{Key{1}, T{10}});
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
		VERIFY(*(--it) == ValueType{Key{1}, T{10}});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it--) == ValueType{Key{1}, T{10}});
		VERIFY(*it == ValueType{Key{2}, T{50}});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, RBeginREndTest)
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

	// https://en.cppreference.com/w/cpp/container/map/rbegin
	{
		const hamon::map<int, hamon::string_view> coins
		{
			{ 10, "dime"},
			{100, "dollar"},
			{ 50, "half dollar"},
			{  5, "nickel"},
			{  1, "penny"},
			{ 25, "quarter"}
		};

		auto it = coins.crbegin();
		EXPECT_TRUE(it != coins.crend());
		EXPECT_EQ(100, it->first);
		EXPECT_EQ("dollar", it->second);
		++it;
		EXPECT_TRUE(it != coins.crend());
		EXPECT_EQ(50, it->first);
		EXPECT_EQ("half dollar", it->second);
		++it;
		EXPECT_TRUE(it != coins.crend());
		EXPECT_EQ(25, it->first);
		EXPECT_EQ("quarter", it->second);
		++it;
		EXPECT_TRUE(it != coins.crend());
		EXPECT_EQ(10, it->first);
		EXPECT_EQ("dime", it->second);
		++it;
		EXPECT_TRUE(it != coins.crend());
		EXPECT_EQ(5, it->first);
		EXPECT_EQ("nickel", it->second);
		++it;
		EXPECT_TRUE(it != coins.crend());
		EXPECT_EQ(1, it->first);
		EXPECT_EQ("penny", it->second);
		++it;
		EXPECT_TRUE(it == coins.crend());
	}
}

}	// namespace rbegin_rend_test

}	// namespace hamon_map_test
