﻿/**
 *	@file	unit_test_set_insert_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	pair<iterator,bool> insert(value_type&& x);
 */

#include <hamon/set/set.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace insert_move_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

struct S1
{
	int x;
	int y;

	constexpr S1(int i) : x(i), y(0) {}
	constexpr S1(int i, int j) : x(i), y(j) {}

	S1(S1&&)                 = default;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;

	friend constexpr bool operator<(S1 const& lhs, S1 const& rhs)
	{
		return lhs.x < rhs.x;
	}
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

	S2(S2 const&)            = delete;
	S2& operator=(S2&&)      = delete;
	S2& operator=(S2 const&) = delete;

	friend bool operator<(S2 const& lhs, S2 const& rhs)
	{
		return lhs.value < rhs.value;
	}
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

	ThrowOnMove(ThrowOnMove const&)            = delete;
	ThrowOnMove& operator=(ThrowOnMove&&)      = delete;
	ThrowOnMove& operator=(ThrowOnMove const&) = delete;

	friend bool operator<(ThrowOnMove const& lhs, ThrowOnMove const& rhs)
	{
		return lhs.value < rhs.value;
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<Key>;
	using ValueType = typename Set::value_type;
	using Iterator = typename Set::iterator;
#if defined(HAMON_USE_STD_SET)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	Set v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<ValueType&&>())), "");

	{
		auto r = v.insert(ValueType{10});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{10});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == false);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{15});
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{20});
		VERIFY(r.first  == hamon::next(v.begin(), 2));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{5});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ ==  5);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{20});
		VERIFY(r.first  == hamon::next(v.begin(), 3));
		VERIFY(r.second == false);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ ==  5);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}

	return true;
}

SET_TEST_CONSTEXPR bool test2()
{
	hamon::set<S1> v;

	{
		auto r = v.insert(S1{1});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 0);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{1});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == false);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 0);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{2, 10});
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 0);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{2, 20});
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 0);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{3, 20});
		VERIFY(r.first  == hamon::next(v.begin(), 2));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 0);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{0, 30});
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(it->x == 0);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 0);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, InsertMoveTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	S2::s_ctor_count = 0;
	S2::s_move_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::set<S2> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_move_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.insert(S2{10});
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S2::s_ctor_count);
		EXPECT_EQ(1, S2::s_move_ctor_count);
		EXPECT_EQ(1, S2::s_dtor_count);

		v.insert(S2{10});
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(1, S2::s_move_ctor_count);
		EXPECT_EQ(2, S2::s_dtor_count);

		v.insert(S2{20});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(2, S2::s_move_ctor_count);
		EXPECT_EQ(3, S2::s_dtor_count);
	}
	EXPECT_EQ(3, S2::s_ctor_count);
	EXPECT_EQ(2, S2::s_move_ctor_count);
	EXPECT_EQ(5, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::set<ThrowOnMove> v;

		v.emplace(1);
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.insert(ThrowOnMove{10}), ThrowOnMove::Exception);
		EXPECT_EQ(1u, v.size());

		v.emplace(2);
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.insert(ThrowOnMove{10}), ThrowOnMove::Exception);
		EXPECT_EQ(2u, v.size());

		v.emplace(10);
		EXPECT_EQ(3u, v.size());

		EXPECT_NO_THROW(v.insert(ThrowOnMove{10}));
		EXPECT_EQ(3u, v.size());
		{
			auto it = v.begin();
			EXPECT_EQ(1, (it++)->value);
			EXPECT_EQ(2, (it++)->value);
			EXPECT_EQ(10, (it++)->value);
			EXPECT_TRUE(it == v.end());
		}
	}
#endif

	// https://en.cppreference.com/w/cpp/container/set/insert
	{
		hamon::set<int> set;

		auto result_1 = set.insert(3);
		EXPECT_TRUE(result_1.first != set.end()); // it is a valid iterator
		EXPECT_TRUE(*result_1.first == 3);
		EXPECT_TRUE( result_1.second);

		auto result_2 = set.insert(3);
		EXPECT_TRUE(result_2.first == result_1.first); // same iterator
		EXPECT_TRUE(*result_2.first == 3);
		EXPECT_TRUE(!result_2.second);
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace insert_move_test

}	// namespace hamon_set_test
