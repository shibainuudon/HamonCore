/**
 *	@file	unit_test_map_erase_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> size_type erase(K&& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_map_test
{

namespace erase_heterogeneous_test
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
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T, hamon::less<>>;
	using ValueType = typename Map::value_type;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_MAP)
	static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int>())), "");
#endif

	Map v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};
	VERIFY(v.size() == 4);

	{
		auto r = v.erase(1);
		VERIFY(r == 1);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(2);
		VERIFY(r == 0);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.erase(5);
		VERIFY(r == 1);
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

struct S
{
	static int s_ctor_count;
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	~S()
	{
		++s_dtor_count;
	}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;

	friend bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

GTEST_TEST(MapTest, EraseHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	S::s_ctor_count = 0;
	S::s_dtor_count = 0;
	{
		hamon::map<S, float, hamon::less<>> v;
		v.emplace(1, 10.5f);
		v.emplace(2, 20.5f);
		v.emplace(3, 30.5f);
		v.emplace(4, 40.5f);
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.erase(2);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(1, S::s_dtor_count);

		v.erase(3);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);

		v.erase(2);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);

		v.erase(5);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(4, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);
	}
	EXPECT_EQ(4, S::s_ctor_count);
	EXPECT_EQ(4, S::s_dtor_count);
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace erase_heterogeneous_test

}	// namespace hamon_map_test

#endif
