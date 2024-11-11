/**
 *	@file	unit_test_map_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	void clear() noexcept;
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace clear_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

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
};

int S::s_ctor_count = 0;
int S::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;

	Map v;

	static_assert(hamon::is_same<decltype(v.clear()), void>::value, "");
	static_assert(noexcept(v.clear()), "");

	VERIFY(v.empty() == true);
	v.clear();
	VERIFY(v.empty() == true);
	v.emplace(Key{1}, T{2});
	VERIFY(v.empty() == false);
	v.clear();
	VERIFY(v.empty() == true);

	return true;
}

#undef VERIFY

template <typename Key, typename T, typename C>
std::string ToString(const hamon::map<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MapTest, ClearTest)
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
		hamon::map<int, S> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.emplace(0, 10);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.emplace(1, 20);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S::s_ctor_count);
		EXPECT_EQ(0, S::s_dtor_count);

		v.clear();
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(2, S::s_ctor_count);
		EXPECT_EQ(2, S::s_dtor_count);
	}
	EXPECT_EQ(2, S::s_ctor_count);
	EXPECT_EQ(2, S::s_dtor_count);

	// https://en.cppreference.com/w/cpp/container/map/clear
	{
		hamon::map<int, char> container {{1, 'x'}, {2, 'y'}, {3, 'z'}};
		EXPECT_EQ("[1] = x, [2] = y, [3] = z, ", ToString(container));
		container.clear();
		EXPECT_EQ("", ToString(container));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace clear_test

}	// namespace hamon_map_test
