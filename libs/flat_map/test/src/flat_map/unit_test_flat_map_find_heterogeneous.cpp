/**
 *	@file	unit_test_flat_map_find_heterogeneous.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class K> constexpr iterator find(const K& x);
 *	template<class K> constexpr const_iterator find(const K& x) const;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace find_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_find_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_find_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().find(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map1 = hamon::flat_map<Key, T, hamon::less<>, KeyContainer, MappedContainer>;
	using Map2 = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using Map3 = hamon::flat_map<Key, T, hamon::greater<>, KeyContainer, MappedContainer>;
	using Map4 = hamon::flat_map<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

	static_assert( is_find_invocable<Map1&, int>::value, "");
	static_assert(!is_find_invocable<Map2&, int>::value, "");
	static_assert( is_find_invocable<Map3&, int>::value, "");
	static_assert(!is_find_invocable<Map4&, int>::value, "");

	static_assert( is_find_invocable<Map1 const&, int>::value, "");
	static_assert(!is_find_invocable<Map2 const&, int>::value, "");
	static_assert( is_find_invocable<Map3 const&, int>::value, "");
	static_assert(!is_find_invocable<Map4 const&, int>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<Map1 const&>().find(hamon::declval<int const&>())), typename Map1::const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().find(hamon::declval<int const&>())), typename Map1::iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map1 const&>().find(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().find(hamon::declval<int const&>())), "");

	{
		Map1 v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.find(0) == v.end());
		VERIFY(v.find(1) == (v.begin() + 0));
		VERIFY(v.find(2) == v.end());
		VERIFY(v.find(3) == (v.begin() + 1));
		VERIFY(v.find(4) == (v.begin() + 2));
		VERIFY(v.find(5) == v.end());
		VERIFY(v.find(6) == (v.begin() + 3));
		VERIFY(v.find(7) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(0) == cv.end());
		VERIFY(cv.find(1) == (cv.begin() + 0));
		VERIFY(cv.find(2) == cv.end());
		VERIFY(cv.find(3) == (cv.begin() + 1));
		VERIFY(cv.find(4) == (cv.begin() + 2));
		VERIFY(cv.find(5) == cv.end());
		VERIFY(cv.find(6) == (cv.begin() + 3));
		VERIFY(cv.find(7) == cv.end());
	}
	{
		Map3 v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.find(0) == v.end());
		VERIFY(v.find(1) == (v.begin() + 3));
		VERIFY(v.find(2) == v.end());
		VERIFY(v.find(3) == (v.begin() + 2));
		VERIFY(v.find(4) == (v.begin() + 1));
		VERIFY(v.find(5) == v.end());
		VERIFY(v.find(6) == (v.begin() + 0));
		VERIFY(v.find(7) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(0) == cv.end());
		VERIFY(cv.find(1) == (cv.begin() + 3));
		VERIFY(cv.find(2) == cv.end());
		VERIFY(cv.find(3) == (cv.begin() + 2));
		VERIFY(cv.find(4) == (cv.begin() + 1));
		VERIFY(cv.find(5) == cv.end());
		VERIFY(cv.find(6) == (cv.begin() + 0));
		VERIFY(cv.find(7) == cv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, FindHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<long>>()));

	{
		hamon::flat_map<hamon::string, int, hamon::less<>> fm =
		{
			{"Alice", 3},
			{"Bob",   1},
			{"Carol", 4},
		};

		// lessのvoidに対する特殊化を使用することで、
		// 文字列リテラルをfind()関数の引数として渡した際に、
		// string型の一時オブジェクトが生成されない。
		auto it1 = fm.find((const char*)"Bob");
		EXPECT_TRUE(it1 != fm.end());
		EXPECT_TRUE(it1->second == 1);

		auto it2 = fm.find((const char*)"Eve");
		EXPECT_TRUE(it2 == fm.end());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace find_heterogeneous_test

}	// namespace hamon_flat_map_test
