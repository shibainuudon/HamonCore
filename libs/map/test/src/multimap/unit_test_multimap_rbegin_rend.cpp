/**
 *	@file	unit_test_multimap_rbegin_rend.cpp
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

#include <hamon/map/multimap.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multimap_test
{

namespace rbegin_rend_test
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
		VERIFY(it->second == 40);
		VERIFY(*(++it) == ValueType{Key{4}, T{20}});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == ValueType{Key{4}, T{20}});
		VERIFY(*it == ValueType{Key{2}, T{50}});
		++it;
		VERIFY(*it == ValueType{Key{1}, T{60}});
		it++;
		VERIFY(*it == ValueType{Key{1}, T{30}});
		++it;
		VERIFY(*it == ValueType{Key{1}, T{10}});
		it++;
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
		VERIFY(*it == ValueType{Key{1}, T{30}});
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
		VERIFY(it->second == 40);
		VERIFY(*(++it) == ValueType{Key{4}, T{20}});
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*(it++) == ValueType{Key{4}, T{20}});
		VERIFY(*it == ValueType{Key{2}, T{50}});
		++it;
		VERIFY(*it == ValueType{Key{1}, T{60}});
		it++;
		VERIFY(*it == ValueType{Key{1}, T{30}});
		++it;
		VERIFY(*it == ValueType{Key{1}, T{10}});
		it++;
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
		VERIFY(*it == ValueType{Key{1}, T{30}});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, RBeginREndTest)
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

	// https://en.cppreference.com/w/cpp/container/multimap/rbegin
	{
		hamon::multimap<std::string, int> map
		{
			{"a", 1},
			{"e", 5},
			{"c", 3},
			{"g", 7},
			{"h", 8},
			{"d", 4},
			{"f", 6},
			{"b", 2}
		};

		using Pair = typename hamon::multimap<std::string, int>::value_type;

		// Print out in reverse order using const reverse iterators
		std::stringstream out;
		hamon::for_each(map.crbegin(), map.crend(),
			[&](Pair const& e)
			{
				out << "{ " << e.first << ", " << e.second << " }, ";
			});
		EXPECT_EQ("{ h, 8 }, { g, 7 }, { f, 6 }, { e, 5 }, { d, 4 }, { c, 3 }, { b, 2 }, { a, 1 }, ", out.str());

		map.rbegin()->second = 42; // OK: non-const value is modifiable
//		map.crbegin()->second = 42; // Error: cannot modify the const value

		std::stringstream out2;
		hamon::for_each(map.crbegin(), map.crend(),
			[&](Pair const& e)
			{
				out2 << "{ " << e.first << ", " << e.second << " }, ";
			});
		EXPECT_EQ("{ h, 42 }, { g, 7 }, { f, 6 }, { e, 5 }, { d, 4 }, { c, 3 }, { b, 2 }, { a, 1 }, ", out2.str());
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace rbegin_rend_test

}	// namespace hamon_multimap_test
