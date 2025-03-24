/**
 *	@file	unit_test_unordered_map_insert_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr pair<iterator, bool> insert(value_type&& obj);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace insert_move_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), "");

	Map v;

	{
		auto r = v.insert(ValueType{Key{1}, T{10}});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
	}
	{
		ValueType x{Key{2}, T{10}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{10});
	}
	{
		ValueType x{Key{1}, T{20}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{10});
	}

	v.clear();
	v.max_load_factor(0.9f);

	for (int i = 0; i < 100; ++i)
	{
		ValueType x{static_cast<Key>(i), T{42}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->first == static_cast<Key>(i));
		VERIFY(r.first->second == T{42});
		VERIFY(r.second == true);

		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	VERIFY(v.size() == 100);

	return true;
}

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}

	S1(S1&&)                 = default;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;
};

UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::unordered_map<int, S1>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), "");

	Map v;
	{
		auto r = v.insert(ValueType{1, S1{10, 20}});
		VERIFY(r.first  == v.begin());
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.insert(ValueType{3, S1{30, 40}});
		VERIFY(r.first->first == 3);
		VERIFY(r.first->second.x == 30);
		VERIFY(r.first->second.y == 40);
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(3).x == 30);
		VERIFY(v.at(3).y == 40);
	}
	{
		auto r = v.insert(ValueType{1, S1{50, 60}});
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(3).x == 30);
		VERIFY(v.at(3).y == 40);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, InsertMoveTest)
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

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::unordered_map<int, ThrowOnMove>;
		using ValueType = typename Map::value_type;

		Map v;

		{
			ThrowOnMove t{10};
			ValueType x{1, t};
			EXPECT_THROW(v.insert(hamon::move(x)), ThrowOnMove::Exception);
			EXPECT_EQ(0u, v.size());
		}
		{
			ThrowOnMove const t{10};
			ValueType const x{1, t};
			v.insert(x);
			EXPECT_EQ(1u, v.size());
		}
#if !defined(HAMON_USE_STD_UNORDERED_MAP)	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		{
			ThrowOnMove t{10};
			ValueType x{1, t};
			EXPECT_NO_THROW(v.insert(hamon::move(x)));
			EXPECT_EQ(1u, v.size());
		}
#endif
	}
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace insert_move_test

}	// namespace hamon_unordered_map_test
