/**
 *	@file	unit_test_flat_multimap_contains_heterogeneous.cpp
 *
 *	@brief	contains のテスト
 *
 *	template<class K> constexpr bool contains(const K& x) const;
 */

#include <hamon/flat_map/flat_multimap.hpp>
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
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace contains_heterogeneous_test
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
struct is_contains_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_contains_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().contains(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map1 = hamon::flat_multimap<Key, T, hamon::less<>, KeyContainer, MappedContainer>;
	using Map2 = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using Map3 = hamon::flat_multimap<Key, T, hamon::greater<>, KeyContainer, MappedContainer>;
	using Map4 = hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

	static_assert( is_contains_invocable<Map1&, int>::value, "");
	static_assert(!is_contains_invocable<Map2&, int>::value, "");
	static_assert( is_contains_invocable<Map3&, int>::value, "");
	static_assert(!is_contains_invocable<Map4&, int>::value, "");

	static_assert( is_contains_invocable<Map1 const&, int>::value, "");
	static_assert(!is_contains_invocable<Map2 const&, int>::value, "");
	static_assert( is_contains_invocable<Map3 const&, int>::value, "");
	static_assert(!is_contains_invocable<Map4 const&, int>::value, "");

	using Map = Map1;
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<int const&>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<int&&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int&&>())), "");

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{4}, T{40}},
	};
	VERIFY(!v.contains(0));
	VERIFY( v.contains(1));
	VERIFY(!v.contains(2));
	VERIFY( v.contains(3));
	VERIFY( v.contains(4));
	VERIFY(!v.contains(5));

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, ContainsHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<long>>()));

	{
		hamon::flat_multimap<hamon::string, int, hamon::less<>> fm =
		{
			{"Alice", 3},
			{"Bob",   1},
			{"Carol", 4},
			{"Alice", 2},
		};

		// lessのvoidに対する特殊化を使用することで、
		// 文字列リテラルをcontains()関数の引数として渡した際に、
		// string型の一時オブジェクトが生成されない。
		EXPECT_TRUE (fm.contains((const char*)"Alice"));
		EXPECT_TRUE (fm.contains((const char*)"Bob"));
		EXPECT_FALSE(fm.contains((const char*)"Eve"));
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace contains_heterogeneous_test

}	// namespace hamon_flat_multimap_test
