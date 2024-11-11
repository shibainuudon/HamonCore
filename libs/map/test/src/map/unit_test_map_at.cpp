/**
 *	@file	unit_test_map_at.cpp
 *
 *	@brief	at のテスト
 *
 *	mapped_type&       at(const key_type& x);
 *	const mapped_type& at(const key_type& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace at_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using MappedType = typename Map::mapped_type;
	using ValueType = typename Map::value_type;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.at(hamon::declval<Key const&>())), MappedType&>::value, "");
		static_assert(!noexcept(v.at(hamon::declval<Key const&>())), "");
	}

	Map v
	{
		{Key{2}, T{10}},
		{Key{1}, T{20}},
		{Key{3}, T{30}},
	};

	VERIFY(v.at(Key{1}) == T{20});
	VERIFY(v.at(Key{2}) == T{10});
	VERIFY(v.at(Key{3}) == T{30});

	v.at(Key{3}) = T{40};

	{
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{2}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{40}});
		VERIFY(it == v.end());
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<Key, T>;
	using MappedType = typename Map::mapped_type;

	{
		Map const v;
		static_assert(hamon::is_same<decltype(v.at(hamon::declval<Key const&>())), MappedType const&>::value, "");
		static_assert(!noexcept(v.at(hamon::declval<Key const&>())), "");
	}

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
	};

	VERIFY(v.at(Key{1}) == T{20});
	VERIFY(v.at(Key{3}) == T{10});
	VERIFY(v.at(Key{4}) == T{30});

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, AtTest)
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

	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4834)	// 'nodiscard' 属性を持つ関数の戻り値を破棄しています
HAMON_WARNING_DISABLE_CLANG("-Wunused-result")
	{
		hamon::map<int, float> v
		{
			{ 1, 0.5f },
			{ 7, 1.5f },
			{ 3, 2.5f },
		};

		EXPECT_THROW   (v.at(0), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(1));
		EXPECT_THROW   (v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(3));

		v[0] = 3.5f;

		EXPECT_NO_THROW(v.at(0));
		EXPECT_NO_THROW(v.at(1));
		EXPECT_THROW   (v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(3));
	}
	{
		hamon::map<int, float> const v
		{
			{ 2, 0.5f },
			{ 0, 1.5f },
			{ 3, 2.5f },
		};

		EXPECT_NO_THROW(v.at(0));
		EXPECT_THROW   (v.at(1), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(2));
		EXPECT_NO_THROW(v.at(3));
	}
HAMON_WARNING_POP()
#endif

	// https://en.cppreference.com/w/cpp/container/map/at
	{
		hamon::map<int, char> map {{1, 'a'}, {2, 'b'}};
		EXPECT_TRUE(map.at(1) == 'a');
		EXPECT_TRUE(map.at(2) == 'b');
#if !defined(HAMON_NO_EXCEPTIONS)
		try
		{
			(void)map.at(13);
			GTEST_FAIL();
		}
		catch (const hamon::out_of_range&)
		{
		}
#endif
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace at_test

}	// namespace hamon_map_test
