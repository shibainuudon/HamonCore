/**
 *	@file	unit_test_multiset_insert_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(value_type&& x);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace insert_move_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
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
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using ValueType = typename Set::value_type;
	using Iterator = typename Set::iterator;

	Set v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<ValueType&&>())), "");

	{
		auto r = v.insert(ValueType{10});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{10});
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{15});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{20});
		VERIFY(r == hamon::next(v.begin(), 3));

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{5});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it++ ==  5);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(ValueType{20});
		VERIFY(r == hamon::next(v.begin(), 5));

		VERIFY(v.size() == 6);
		auto it = v.begin();
		VERIFY(*it++ ==  5);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 10);
		VERIFY(*it++ == 15);
		VERIFY(*it++ == 20);
		VERIFY(*it++ == 20);
		VERIFY(it == v.end());
	}

	return true;
}

MULTISET_TEST_CONSTEXPR bool test2()
{
	hamon::multiset<S1> v;

	{
		auto r = v.insert(S1{1, 10});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{1, 20});
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{2, 10});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{2, 20});
		VERIFY(r == hamon::next(v.begin(), 3));

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{3, 20});
		VERIFY(r == hamon::next(v.begin(), 4));

		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(S1{0, 30});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 6);
		auto it = v.begin();
		VERIFY(it->x == 0);
		VERIFY(it->y == 30);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 1);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 10);
		++it;
		VERIFY(it->x == 2);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it->x == 3);
		VERIFY(it->y == 20);
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, InsertMoveTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	S2::s_ctor_count = 0;
	S2::s_move_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::multiset<S2> v;
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
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(2, S2::s_move_ctor_count);
		EXPECT_EQ(2, S2::s_dtor_count);

		v.insert(S2{20});
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(3, S2::s_move_ctor_count);
		EXPECT_EQ(3, S2::s_dtor_count);
	}
	EXPECT_EQ(3, S2::s_ctor_count);
	EXPECT_EQ(3, S2::s_move_ctor_count);
	EXPECT_EQ(6, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::multiset<ThrowOnMove> v;

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

		EXPECT_THROW(v.insert(ThrowOnMove{10}), ThrowOnMove::Exception);
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
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace insert_move_test

}	// namespace hamon_multiset_test
