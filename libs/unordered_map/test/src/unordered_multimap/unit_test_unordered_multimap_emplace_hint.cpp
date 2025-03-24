/**
 *	@file	unit_test_unordered_multimap_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple/forward_as_tuple.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace emplace_hint_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), "");

	Map v;
	v.max_load_factor(1.2f);

	{
		auto r = v.emplace_hint(v.begin(), Key{1}, T{10});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		auto r = v.emplace_hint(v.begin(), Key{1}, T{20});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{20});

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType const t{Key{2}, T{30}};
		auto r = v.emplace_hint(v.begin(), t);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType const t{Key{2}, T{40}};
		auto r = v.emplace_hint(v.begin(), t);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{40});

		VERIFY(v.size() == 4);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType t{Key{2}, T{50}};
		auto r = v.emplace_hint(v.begin(), hamon::move(t));
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{50});

		VERIFY(v.size() == 5);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		ValueType t{Key{0}, T{60}};
		auto r = v.emplace_hint(v.begin(), hamon::move(t));
		VERIFY(r->first == Key{0});
		VERIFY(r->second == T{60});

		VERIFY(v.size() == 6);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	for (int i = 0; i < 100; ++i)
	{
		auto r = v.emplace_hint(v.end(), static_cast<Key>(i), T{42});
		VERIFY(r->first == static_cast<Key>(i));
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

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
#if defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	hamon::unordered_multimap<int, S1> v;

	{
		auto r = v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(v.size() == 1);
	}
	{
		auto r = v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(30, 40));
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 30);
		VERIFY(r->second.y == 40);

		VERIFY(v.size() == 2);
	}
	{
		auto r = v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
		VERIFY(r->first == 2);
		VERIFY(r->second.x == 50);
		VERIFY(r->second.y == 60);

		VERIFY(v.size() == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, EmplaceHintTest)
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
#if defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
		namespace ns = std;
#else
		namespace ns = hamon;
#endif

		hamon::unordered_multimap<int, ThrowIfNegative> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(-1)),
			ThrowIfNegative::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10));
		EXPECT_EQ(1u, v.size());

		v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(11));
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(3),
			ns::forward_as_tuple(-10)),
			ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(-10)),
			ThrowIfNegative::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_NO_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(12)));
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_unordered_multimap_test
