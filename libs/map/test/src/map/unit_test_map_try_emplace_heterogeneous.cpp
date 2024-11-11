/**
 *	@file	unit_test_map_try_emplace_heterogeneous.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class K, class... Args>
 *	pair<iterator, bool> try_emplace(K&& k, Args&&... args);
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_map_test
{

namespace try_emplace_heterogeneous_test
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

MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, float, hamon::less<>>;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.try_emplace(hamon::declval<int const&>(), hamon::declval<float>())), Result>::value, "");
		static_assert(hamon::is_same<decltype(v.try_emplace(hamon::declval<int&&>(), hamon::declval<float>())), Result>::value, "");
		static_assert(!noexcept(v.try_emplace(hamon::declval<int const&>(), hamon::declval<float>())), "");
		static_assert(!noexcept(v.try_emplace(hamon::declval<int&&>(), hamon::declval<float>())), "");
	}

	Map v;
	{
		auto r = v.try_emplace(1, 0.5f);
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second == 0.5f);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.try_emplace(1, 1.5f);
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == false);

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second == 0.5f);
		++it;
		VERIFY(it == v.end());
	}
	{
		auto r = v.try_emplace(2, 2.5f);
		VERIFY(r.first  == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second == 0.5f);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second == 2.5f);
		++it;
		VERIFY(it == v.end());
	}
	{
		int const k = 0;
		auto r = v.try_emplace(k, 3.5f);
		VERIFY(r.first  == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->first == 0);
		VERIFY(it->second == 3.5f);
		++it;
		VERIFY(it->first == 1);
		VERIFY(it->second == 0.5f);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second == 2.5f);
		++it;
		VERIFY(it == v.end());
	}
	{
		int const k = 2;
		auto r = v.try_emplace(k, 4.5f);
		VERIFY(r.first  == hamon::next(v.begin(), 2));
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->first == 0);
		VERIFY(it->second == 3.5f);
		++it;
		VERIFY(it->first == 1);
		VERIFY(it->second == 0.5f);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second == 2.5f);
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, TryEmplaceHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test());

	S2::s_ctor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::map<Key, S2, hamon::less<>> v;
		EXPECT_EQ(0u, v.size());
		EXPECT_EQ(0, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.try_emplace(0, 10);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		v.try_emplace(1, 20);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);

		// 要素が挿入されないときは一時オブジェクトは作成されない
		v.try_emplace(0, 30);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(2, S2::s_ctor_count);
		EXPECT_EQ(0, S2::s_dtor_count);
	}
	EXPECT_EQ(2, S2::s_ctor_count);
	EXPECT_EQ(2, S2::s_dtor_count);

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::map<Key, MayThrow, hamon::less<>> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.try_emplace(1, -1), MayThrow::Exception);
		EXPECT_EQ(0u, v.size());

		v.try_emplace(1, 10);
		EXPECT_EQ(1u, v.size());

		// 要素が挿入されないときは一時オブジェクトは作成されない
		EXPECT_NO_THROW(v.try_emplace(1, -1));
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.try_emplace(2, -10), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.try_emplace(3, -20), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());

		v.try_emplace(2, 11);
		EXPECT_EQ(2u, v.size());

		v.try_emplace(3, 12);
		EXPECT_EQ(3u, v.size());

		EXPECT_NO_THROW(v.try_emplace(2, -12));
		EXPECT_EQ(3u, v.size());

		EXPECT_NO_THROW(v.try_emplace(3, -20));
		EXPECT_EQ(3u, v.size());
	}
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace try_emplace_heterogeneous_test

}	// namespace hamon_map_test

#endif
