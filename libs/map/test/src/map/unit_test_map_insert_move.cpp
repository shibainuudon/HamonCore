﻿/**
 *	@file	unit_test_map_insert_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	pair<iterator, bool> insert(value_type&& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace insert_move_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

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

struct S2
{
	static int s_ctor_count;
	static int s_move_ctor_count;
	static int s_dtor_count;

	int value;

	S2(int v) : value(v)
	{
		++s_ctor_count;
	}

	S2(S2&& x) : value(x.value)
	{
		++s_move_ctor_count;
	}

	~S2()
	{
		++s_dtor_count;
	}

	S2(S2 const&)            = default;
	S2& operator=(S2&&)      = delete;
	S2& operator=(S2 const&) = delete;
};

int S2::s_ctor_count = 0;
int S2::s_move_ctor_count = 0;
int S2::s_dtor_count = 0;

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove(int v) : value(v)
	{}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}

	ThrowOnMove(ThrowOnMove const&)            = default;
	ThrowOnMove& operator=(ThrowOnMove&&)      = delete;
	ThrowOnMove& operator=(ThrowOnMove const&) = delete;
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	Map v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<ValueType&&>())), "");

	{
		auto r = v.insert(ValueType{Key{1}, T{10}});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{Key{1}, T{20}});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == false);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v.end());
	}
	{
		ValueType x{Key{2}, T{20}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{Key{3}, T{10}});
		VERIFY(r.first  == hamon::next(v.begin(), 2));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}
	{
		ValueType x{Key{0}, T{30}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{30}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{Key{2}, T{40}});
		VERIFY(r.first  == hamon::next(v.begin(), 2));
		VERIFY(r.second == false);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{30}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}

	return true;
}

MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<int, S1>;
	using ValueType = typename Map::value_type;

	Map v;

	{
		auto r = v.insert(ValueType{1, S1{10, 20}});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second.x == 10);
		VERIFY(it->second.y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		ValueType x{3, S1{30, 40}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second.x == 10);
		VERIFY(it->second.y == 20);
		++it;
		VERIFY(it->first == 3);
		VERIFY(it->second.x == 30);
		VERIFY(it->second.y == 40);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{2, S1{50, 60}});
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second.x == 10);
		VERIFY(it->second.y == 20);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second.x == 50);
		VERIFY(it->second.y == 60);
		++it;
		VERIFY(it->first == 3);
		VERIFY(it->second.x == 30);
		VERIFY(it->second.y == 40);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{3, S1{70, 80}});
		VERIFY(r.first  == hamon::next(v.begin(), 2));
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second.x == 10);
		VERIFY(it->second.y == 20);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second.x == 50);
		VERIFY(it->second.y == 60);
		++it;
		VERIFY(it->first == 3);
		VERIFY(it->second.x == 30);
		VERIFY(it->second.y == 40);
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, InsertMoveTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	S2::s_ctor_count = 0;
	S2::s_move_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		using Map = hamon::map<int, S2>;
		using ValueType = typename Map::value_type;

		Map v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_move_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.insert(ValueType{3, S2{10}});
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S2::s_ctor_count);
		EXPECT_EQ(2, S2::s_move_ctor_count);
		EXPECT_EQ(2, S2::s_dtor_count);

		v.insert(ValueType{1, S2{20}});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(4, S2::s_move_ctor_count);
		EXPECT_EQ(4, S2::s_dtor_count);

		v.insert(ValueType{3, S2{30}});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(5, S2::s_move_ctor_count);
		EXPECT_EQ(6, S2::s_dtor_count);
	}
	EXPECT_EQ(3, S2::s_ctor_count);
	EXPECT_EQ(5, S2::s_move_ctor_count);
	EXPECT_EQ(8, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
#if defined(HAMON_USE_STD_MAP)
		namespace ns = std;
#else
		namespace ns = hamon;
#endif
		using Map = hamon::map<int, ThrowOnMove>;
		using ValueType = typename Map::value_type;

		Map v;

		{
			ThrowOnMove t{10};
			ValueType x{1, t};
			EXPECT_THROW(v.insert(hamon::move(x)), ThrowOnMove::Exception);
			EXPECT_EQ(0u, v.size());
		}

		v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10));
		EXPECT_EQ(1u, v.size());

		{
			ThrowOnMove t{10};
			ValueType x{1, t};
			EXPECT_NO_THROW(v.insert(hamon::move(x)));
			EXPECT_EQ(1u, v.size());
		}
	}
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_move_test

}	// namespace hamon_map_test
