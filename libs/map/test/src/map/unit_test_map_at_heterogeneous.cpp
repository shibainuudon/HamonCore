/**
 *	@file	unit_test_map_at_heterogeneous.cpp
 *
 *	@brief	at のテスト
 *
 *	template<class K> mapped_type&       at(const K& x);
 *	template<class K> const mapped_type& at(const K& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_map_test
{

namespace at_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct Key
{
	int value;

	explicit constexpr Key(int v) : value(v) {}

	friend constexpr bool operator==(Key const& lhs, Key const& rhs)
	{
		return lhs.value == rhs.value;
	}

	friend constexpr bool operator==(Key const& lhs, int rhs)
	{
		return lhs.value == rhs;
	}

	friend constexpr bool operator<(Key const& lhs, Key const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(Key const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, Key const& rhs)
	{
		return lhs < rhs.value;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T, hamon::less<>>;
	using MappedType = typename Map::mapped_type;
	using ValueType = typename Map::value_type;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.at(hamon::declval<int const&>())), MappedType&>::value, "");
		static_assert(!noexcept(v.at(hamon::declval<int const&>())), "");
	}

	Map v
	{
		{Key{2}, T{10}},
		{Key{1}, T{20}},
		{Key{3}, T{30}},
	};

	VERIFY(v.at(1) == T{20});
	VERIFY(v.at(2) == T{10});
	VERIFY(v.at(3) == T{30});

	v.at(3) = T{40};

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

template <typename T>
MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<Key, T, hamon::less<>>;
	using MappedType = typename Map::mapped_type;

	{
		Map const v;
		static_assert(hamon::is_same<decltype(v.at(hamon::declval<int const&>())), MappedType const&>::value, "");
		static_assert(!noexcept(v.at(hamon::declval<int const&>())), "");
	}

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
	};

	VERIFY(v.at(1) == T{20});
	VERIFY(v.at(3) == T{10});
	VERIFY(v.at(4) == T{30});

	return true;
}

#undef VERIFY

struct LightKey { int o; };
struct HeavyKey { int o[1000]; };

// The container must use std::less<> (or other transparent Comparator) to
// access overloads (3,4). This includes standard overloads, such as
// comparison between std::string and std::string_view.
bool operator<(const HeavyKey& x, const LightKey& y) { return x.o[0] < y.o; }
bool operator<(const LightKey& x, const HeavyKey& y) { return x.o < y.o[0]; }
bool operator<(const HeavyKey& x, const HeavyKey& y) { return x.o[0] < y.o[0]; }

GTEST_TEST(MapTest, AtHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4834)	// 'nodiscard' 属性を持つ関数の戻り値を破棄しています
	{
		hamon::map<Key, float, hamon::less<>> v
		{
			{ Key{1}, 0.5f },
			{ Key{7}, 1.5f },
			{ Key{3}, 2.5f },
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
		hamon::map<Key, float, hamon::less<>> const v
		{
			{ Key{2}, 0.5f },
			{ Key{0}, 1.5f },
			{ Key{3}, 2.5f },
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
		// Transparent comparison demo.
		hamon::map<HeavyKey, char, hamon::less<>> map2 {{{1}, 'a'}, {{2}, 'b'}};
		assert(map2.at(LightKey {1}) == 'a');
		assert(map2.at(LightKey {2}) == 'b');
#if !defined(HAMON_NO_EXCEPTIONS)
		try
		{
			(void)map2.at(LightKey {13});
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

}	// namespace at_heterogeneous_test

}	// namespace hamon_map_test

#endif
