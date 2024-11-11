/**
 *	@file	unit_test_multimap_begin_end.cpp
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

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multimap_test
{

namespace begin_end_test
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
		VERIFY(*(++it) == ValueType{Key{1}, T{30}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == ValueType{Key{1}, T{30}});
		VERIFY(*it == ValueType{Key{1}, T{60}});
		++it;
		VERIFY(*it == ValueType{Key{2}, T{50}});
		it++;
		VERIFY(*it == ValueType{Key{4}, T{20}});
		++it;
		VERIFY(*it == ValueType{Key{4}, T{40}});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == ValueType{Key{4}, T{40}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == ValueType{Key{4}, T{40}});
		VERIFY(*it == ValueType{Key{4}, T{20}});
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
		VERIFY(*(++it) == ValueType{Key{1}, T{30}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it++) == ValueType{Key{1}, T{30}});
		VERIFY(*it == ValueType{Key{1}, T{60}});
		++it;
		VERIFY(*it == ValueType{Key{2}, T{50}});
		it++;
		VERIFY(*it == ValueType{Key{4}, T{20}});
		++it;
		VERIFY(*it == ValueType{Key{4}, T{40}});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
		VERIFY(*(--it) == ValueType{Key{4}, T{40}});
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*(it--) == ValueType{Key{4}, T{40}});
		VERIFY(*it == ValueType{Key{4}, T{20}});
	}

	return true;
}

#undef VERIFY

template <typename Key, typename T, typename C>
std::string ToString(const hamon::multimap<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MultimapTest, BeginEndTest)
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

	// https://en.cppreference.com/w/cpp/container/multimap/begin
	{
		hamon::multimap<std::size_t, std::string> mmap;
		using Pair = typename hamon::multimap<std::size_t, std::string>::value_type;
		EXPECT_TRUE(mmap.begin() == mmap.end());   // OK
		EXPECT_TRUE(mmap.cbegin() == mmap.cend()); // OK

		mmap.insert({8u, "LONG"});
		EXPECT_TRUE((*mmap.cbegin() == Pair{8u, "LONG"}));
		EXPECT_TRUE(mmap.begin() != mmap.end());   // OK
		EXPECT_TRUE(mmap.cbegin() != mmap.cend()); // OK
		mmap.begin()->second = "long";
		EXPECT_TRUE((*mmap.cbegin() == Pair{8u, "long"}));

		mmap.insert({4u, "int"});
		EXPECT_TRUE((*mmap.cbegin() == Pair{4u, "int"}));

		mmap.insert({2u, "short"});
		EXPECT_TRUE((*mmap.cbegin() == Pair{2u, "short"}));

		mmap.insert({1u, "char"});
		EXPECT_TRUE((*mmap.cbegin() == Pair{1u, "char"}));

		mmap.insert({{4u, "float"}, {8u, "double"}});
		EXPECT_EQ("[1] = char, [2] = short, [4] = int, [4] = float, [8] = long, [8] = double, ", ToString(mmap));
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_multimap_test
