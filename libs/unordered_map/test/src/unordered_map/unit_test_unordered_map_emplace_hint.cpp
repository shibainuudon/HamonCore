/**
 *	@file	unit_test_unordered_map_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple/forward_as_tuple.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace emplace_hint_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), "");

	Map v;

	{
		auto r = v.emplace_hint(v.end(), Key{1}, T{10});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1) == 10);
	}
	{
		auto r = v.emplace_hint(v.begin(), Key{1}, T{20});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1) == 10);
	}
	{
		ValueType const t{Key{2}, T{30}};
		auto r = v.emplace_hint(v.cend(), t);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1) == 10);
		VERIFY(v.at(2) == 30);
	}
	{
		ValueType const t{Key{2}, T{40}};
		auto r = v.emplace_hint(v.cbegin(), t);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1) == 10);
		VERIFY(v.at(2) == 30);
	}
	{
		ValueType t{Key{2}, T{50}};
		auto r = v.emplace_hint(v.end(), hamon::move(t));
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1) == 10);
		VERIFY(v.at(2) == 30);
	}
	{
		ValueType t{Key{0}, T{60}};
		auto r = v.emplace_hint(v.end(), hamon::move(t));
		VERIFY(r->first == Key{0});
		VERIFY(r->second == T{60});

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(0) == 60);
		VERIFY(v.at(1) == 10);
		VERIFY(v.at(2) == 30);
	}

	for (int i = 0; i < 100; ++i)
	{
		auto r = v.emplace_hint(v.end(), static_cast<Key>(i + 10), T{42});
		VERIFY(r->first == static_cast<Key>(i + 10));
		VERIFY(r->second == T{42});

		VERIFY(v.load_factor() <= v.max_load_factor());
	}

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
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	hamon::unordered_map<int, S1> v;

	{
		auto r = v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(30, 40));
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
		VERIFY(r->first == 2);
		VERIFY(r->second.x == 50);
		VERIFY(r->second.y == 60);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(2).x == 50);
		VERIFY(v.at(2).y == 60);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, EmplaceHintTest)
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
#if defined(HAMON_USE_STD_UNORDERED_MAP)
		namespace ns = std;
#else
		namespace ns = hamon;
#endif

		hamon::unordered_map<int, ThrowIfNegative> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(-1)),
			ThrowIfNegative::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10));
		EXPECT_EQ(1u, v.size());

		v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(11));
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(3),
			ns::forward_as_tuple(-10)),
			ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

#if !defined(HAMON_USE_STD_UNORDERED_MAP)	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		EXPECT_THROW(v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(-10)),
			ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());
#endif

		EXPECT_NO_THROW(v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(12)));
		EXPECT_EQ(2u, v.size());

#if !defined(HAMON_USE_STD_UNORDERED_MAP)	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		EXPECT_NO_THROW(v.emplace_hint(v.begin(),1, -10));
		EXPECT_EQ(2u, v.size());
#endif

		EXPECT_THROW(v.emplace_hint(v.begin(),3, -10), ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_NO_THROW(v.emplace_hint(v.begin(),3, 10));
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_unordered_map_test
