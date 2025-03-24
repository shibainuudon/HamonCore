/**
 *	@file	unit_test_unordered_map_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr pair<iterator, bool> emplace(Args&&... args);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace emplace_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_map<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<ValueType const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<Key>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<Key>(), hamon::declval<T>())), "");

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
#if 0
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	hamon::unordered_map<int, S1> v;

	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(30, 40));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == false);

		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second.x == 50);
		VERIFY(r.first->second.y == 60);
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(2).x == 50);
		VERIFY(v.at(2).y == 60);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, EmplaceTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace emplace_test

}	// namespace hamon_unordered_map_test
