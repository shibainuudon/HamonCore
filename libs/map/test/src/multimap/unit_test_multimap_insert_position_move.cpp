/**
 *	@file	unit_test_multimap_insert_position_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(const_iterator position, value_type&& x);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/iterator.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace insert_position_move_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
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
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	Map v;

	static_assert(hamon::is_same<decltype(v.insert(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(!noexcept(v.insert(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");

	{
		auto r = v.insert(v.end(), ValueType{Key{1}, T{10}});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(v.begin(), ValueType{Key{1}, T{20}});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v.end());
	}
	{
		ValueType x{Key{2}, T{20}};
		auto r = v.insert(hamon::next(v.begin(), 1), hamon::move(x));
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(hamon::next(v.begin(), 2), ValueType{Key{3}, T{10}});
		VERIFY(r == hamon::next(v.begin(), 3));

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}
	{
		ValueType x{Key{0}, T{30}};
		auto r = v.insert(hamon::next(v.begin(), 0), hamon::move(x));
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{30}});
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.insert(hamon::next(v.begin(), 3), ValueType{Key{2}, T{40}});
		VERIFY(r == hamon::next(v.begin(), 3));

		VERIFY(v.size() == 6);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{30}});
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}

	return true;
}

MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::multimap<int, S1>;
	using ValueType = typename Map::value_type;

	Map v;

	{
		auto r = v.insert(v.end(), ValueType{1, S1{10, 20}});
		VERIFY(r == hamon::next(v.begin(), 0));

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
		auto r = v.insert(v.begin(), hamon::move(x));
		VERIFY(r == hamon::next(v.begin(), 1));

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
		auto r = v.insert(v.begin(), ValueType{2, S1{50, 60}});
		VERIFY(r == hamon::next(v.begin(), 1));

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
		auto r = v.insert(v.begin(), ValueType{3, S1{70, 80}});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 4);
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
		VERIFY(it->second.x == 70);
		VERIFY(it->second.y == 80);
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

GTEST_TEST(MultimapTest, InsertPositionMoveTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	S2::s_ctor_count = 0;
	S2::s_move_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		using Map = hamon::multimap<int, S2>;
		using ValueType = typename Map::value_type;

		Map v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_move_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.insert(v.end(), ValueType{3, S2{10}});
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S2::s_ctor_count);
		EXPECT_EQ(2, S2::s_move_ctor_count);
		EXPECT_EQ(2, S2::s_dtor_count);

		v.insert(v.end(), ValueType{1, S2{20}});
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(4, S2::s_move_ctor_count);
		EXPECT_EQ(4, S2::s_dtor_count);

		v.insert(v.end(), ValueType{3, S2{30}});
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(6, S2::s_move_ctor_count);
		EXPECT_EQ(6, S2::s_dtor_count);
	}
	EXPECT_EQ(3, S2::s_ctor_count);
	EXPECT_EQ(6, S2::s_move_ctor_count);
	EXPECT_EQ(9, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
#if defined(HAMON_USE_STD_MULTIMAP)
		namespace ns = std;
#else
		namespace ns = hamon;
#endif
		using Map = hamon::multimap<int, ThrowOnMove>;
		using ValueType = typename Map::value_type;

		Map v;

		{
			ThrowOnMove t{10};
			ValueType x{1, t};
			EXPECT_THROW(v.insert(v.end(), hamon::move(x)), ThrowOnMove::Exception);
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
			EXPECT_THROW(v.insert(v.end(), hamon::move(x)), ThrowOnMove::Exception);
			EXPECT_EQ(1u, v.size());
		}
	}
#endif
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_position_move_test

}	// namespace hamon_multimap_test
