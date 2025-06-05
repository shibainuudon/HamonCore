/**
 *	@file	unit_test_flat_multimap_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class P> constexpr iterator insert(P&& x);
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
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace insert_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using Iterator = typename Map::iterator;

	// from std::pair
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, int>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<double, long>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, int>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<double, long>>())), "");
	{
		Map v;
		{
			auto r = v.insert(std::make_pair(1, 10.0f));
			VERIFY(r->first == Key{1});
			VERIFY(r->second == T{10});
		}
		VERIFY(v.size() == 1);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		{
			auto const p = std::make_pair(char{2}, 20.0);
			auto r = v.insert(p);
			VERIFY(r->first == Key{2});
			VERIFY(r->second == T{20});
		}
		VERIFY(v.size() == 2);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		{
			auto r = v.insert(std::make_pair(short{1}, 30.0f));
			VERIFY(r->first == Key{1});
			VERIFY(r->second == T{30});
		}
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
	}

	// from std::tuple
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<int, int>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<double, long>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<int, int>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<double, long>>())), "");
	{
		Map v;
		{
			auto r = v.insert(std::make_tuple(1, 10.0f));
			VERIFY(r->first == Key{1});
			VERIFY(r->second == T{10});
		}
		VERIFY(v.size() == 1);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		{
			auto const p = std::make_tuple(char{2}, 20.0);
			auto r = v.insert(p);
			VERIFY(r->first == Key{2});
			VERIFY(r->second == T{20});
		}
		VERIFY(v.size() == 2);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		{
			auto r = v.insert(std::make_tuple(short{2}, 30.0f));
			VERIFY(r->first == Key{2});
			VERIFY(r->second == T{30});
		}
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 0);
	}

	// from std::array
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<int, 2>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<char, 2>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<double, 2>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<int, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<char, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<double, 2>>())), "");
	{
		Map v;
		{
			auto r = v.insert(std::array<int, 2>{2, 10});
			VERIFY(r->first == Key{2});
			VERIFY(r->second == T{10});
		}
		VERIFY(v.size() == 1);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		{
			auto const p = std::array<char, 2>{1, 20};
			auto r = v.insert(p);
			VERIFY(r->first == Key{1});
			VERIFY(r->second == T{20});
		}
		VERIFY(v.size() == 2);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		{
			auto r = v.insert(std::array<short, 2>{1, 30});
			VERIFY(r->first == Key{1});
			VERIFY(r->second == T{30});
		}
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
	}

	return true;
}

template <typename Map, typename P, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Map, typename P>
struct is_insert_invocable<Map, P, hamon::void_t<decltype(hamon::declval<Map>().insert(hamon::declval<P>()))>>
	: public hamon::true_type {};

FLAT_MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::flat_multimap<int, int>;

	static_assert( is_insert_invocable<Map&, std::pair<int, int>>::value, "");
	static_assert( is_insert_invocable<Map&, std::pair<char, float>>::value, "");
	static_assert(!is_insert_invocable<Map&, std::pair<int, std::string>>::value, "");
	static_assert( is_insert_invocable<Map&, std::tuple<int, int>>::value, "");
	static_assert( is_insert_invocable<Map&, std::tuple<char, float>>::value, "");
	static_assert(!is_insert_invocable<Map&, std::tuple<int, int, int>>::value, "");
	static_assert( is_insert_invocable<Map&, std::array<int, 2>>::value, "");
	static_assert(!is_insert_invocable<Map&, std::array<int, 3>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, InsertHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<char>, hamon::vector<double>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<short>, hamon::deque<float>, hamon::less<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<int>, hamon::vector<double>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<long>, hamon::deque<float>, hamon::greater<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<double>, hamon::less<int>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_flat_multimap_test
