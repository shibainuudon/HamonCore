/**
 *	@file	unit_test_unordered_multimap_insert_hint_copy.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator hint, const value_type& obj);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace insert_hint_copy_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_multimap<Key, T>;
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
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
	}
	{
		ValueType const x{Key{2}, T{10}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
	}
	{
		ValueType const x{Key{1}, T{20}};
		auto r = v.insert(v.end(), x);
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{20});

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
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

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::unordered_multimap<int, S1>;
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
	}
	{
		ValueType const x{3, S1{30, 40}};
		auto r = v.insert(v.cend(), x);
		VERIFY(r->first == 3);
		VERIFY(r->second.x == 30);
		VERIFY(r->second.y == 40);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType const x{1, S1{50, 60}};
		auto r = v.insert(v.cbegin(), x);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 50);
		VERIFY(r->second.y == 60);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertHintCopyTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::unordered_multimap<int, ThrowOnCopy>;
		using ValueType = typename Map::value_type;

		Map v;

		{
			ValueType const x{1, ThrowOnCopy{10}};
			EXPECT_THROW(v.insert(v.end(), x), ThrowOnCopy::Exception);
			EXPECT_EQ(0u, v.size());
		}
		{
			ValueType x{1, ThrowOnCopy{10}};
			v.insert(v.end(), hamon::move(x));
			EXPECT_EQ(1u, v.size());
		}
		{
			ValueType const x{1, ThrowOnCopy{10}};
			EXPECT_THROW(v.insert(v.end(), x), ThrowOnCopy::Exception);
			EXPECT_EQ(1u, v.size());
		}
	}
#endif
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_hint_copy_test

}	// namespace hamon_unordered_multimap_test
