/**
 *	@file	unit_test_map_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args> iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/map/map.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace emplace_hint_test
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

	S1(S1&&)                 = delete;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;
};

struct S2
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S2(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S2()
	{
		++s_dtor_count;
	}

	S2(S2&&)                 = delete;
	S2(S2 const&)            = delete;
	S2& operator=(S2&&)      = delete;
	S2& operator=(S2 const&) = delete;
};

int S2::s_ctor_count = 0;
int S2::s_dtor_count = 0;

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	Map v;

	static_assert(hamon::is_same<decltype(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(!noexcept(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(v.emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), "");

	{
		auto r = v.emplace_hint(v.begin(), Key{1}, T{10});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(v.begin(), Key{1}, T{20});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(v.end(), Key{2}, T{20});
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 1), Key{3}, T{10});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.emplace_hint(hamon::next(v.begin(), 1), Key{2}, T{30});
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v.end());
	}

	return true;
}

MAP_TEST_CONSTEXPR bool test2()
{
#if defined(HAMON_USE_STD_MAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	hamon::map<int, S1> v;

	{
		auto r = v.emplace_hint(v.begin(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
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
		auto r = v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(3),
			ns::forward_as_tuple(30, 40));
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
		auto r = v.emplace_hint(hamon::next(v.begin(), 1),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
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
		auto r = v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(70, 80));
		VERIFY(r == hamon::next(v.begin(), 0));

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

GTEST_TEST(MapTest, EmplaceHintTest)
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

#if defined(HAMON_USE_STD_MAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	S2::s_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::map<int, S2> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		// piecewise_construct を使っての挿入は、
		// まず一時オブジェクトを作ってから検索するので、
		// 実際に挿入されない場合でもコンストラクタが実行される

		v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(0),
			ns::forward_as_tuple(10));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(0),
			ns::forward_as_tuple(20));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(1, S2::s_dtor_count);

#if 0	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		v.emplace_hint(v.end(), 0, 30);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(3, S2::s_ctor_count);
		EXPECT_EQ(1, S2::s_dtor_count);
#endif

		v.emplace_hint(v.begin(), 2, 40);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(4, S2::s_ctor_count);
		EXPECT_EQ(1, S2::s_dtor_count);
	}
	EXPECT_EQ(4, S2::s_ctor_count);
	EXPECT_EQ(4, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::map<int, MayThrow> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(-1)),
			MayThrow::Exception);
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
			MayThrow::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(-10)),
			MayThrow::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_NO_THROW(v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(12)));
		EXPECT_EQ(2u, v.size());

#if 0	// 要素が挿入されないときに一時オブジェクトが作成されるかどうかは実装依存
		EXPECT_NO_THROW(v.emplace_hint(v.end(), 1, -10));
		EXPECT_EQ(2u, v.size());
#endif

		EXPECT_THROW(v.emplace_hint(v.end(), 3, -10), MayThrow::Exception);
		EXPECT_EQ(2u, v.size());

		EXPECT_NO_THROW(v.emplace_hint(v.end(), 3, 10));
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_map_test
