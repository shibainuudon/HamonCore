/**
 *	@file	unit_test_unordered_map_insert_hint_copy.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator hint, const value_type& obj);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace insert_hint_copy_test
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
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");

	Map v;

	{
		ValueType const x{Key{1}, T{10}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
	}
	{
		ValueType const x{Key{2}, T{10}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{10});
	}
	{
		ValueType const x{Key{1}, T{20}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{10});
	}

	v.clear();
	v.max_load_factor(0.5f);

	for (int i = 0; i < 100; ++i)
	{
		ValueType const x{static_cast<Key>(i), T{42}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == static_cast<Key>(i));
		VERIFY(r->second == T{42});

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

	S1(S1&&)                 = delete;
	S1(S1 const&)            = default;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;
};

UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::unordered_map<int, S1>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");

	Map v;
	{
		ValueType const x{1, S1{10, 20}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		ValueType const x{3, S1{30, 40}};
		auto r = v.insert(v.cend(), x);
		VERIFY(r->first == 3);
		VERIFY(r->second.x == 30);
		VERIFY(r->second.y == 40);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(3).x == 30);
		VERIFY(v.at(3).y == 40);
	}
	{
		ValueType const x{1, S1{50, 60}};
		auto r = v.insert(v.cbegin(), x);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

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

GTEST_TEST(UnorderedMapTest, InsertHintCopyTest)
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
		using Map = hamon::unordered_map<int, ThrowOnCopy>;
		using ValueType = typename Map::value_type;

		Map v;

		{
			ValueType const x{1, ThrowOnCopy{10}};
			EXPECT_THROW(v.insert(v.cend(), x), ThrowOnCopy::Exception);
			EXPECT_EQ(0u, v.size());
		}
		{
			ValueType x{1, ThrowOnCopy{10}};
			v.insert(v.cend(), hamon::move(x));
			EXPECT_EQ(1u, v.size());
		}
#if !defined(HAMON_USE_STD_UNORDERED_MAP)	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		{
			ValueType const x{1, ThrowOnCopy{10}};
			EXPECT_NO_THROW(v.insert(v.cend(), x));
			EXPECT_EQ(1u, v.size());
		}
#endif
	}
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace insert_hint_copy_test

}	// namespace hamon_unordered_map_test
