/**
 *	@file	unit_test_unordered_map_insert_or_assign_heterogeneous.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class K, class M>
 *	constexpr pair<iterator, bool> insert_or_assign(K&& k, M&& obj);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_unordered_map_test
{

namespace insert_or_assign_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename M, typename = void>
struct is_insert_or_assign_invocable
	: public hamon::false_type {};

template <typename Map, typename K, typename M>
struct is_insert_or_assign_invocable<Map, K, M, hamon::void_t<decltype(hamon::declval<Map>().insert_or_assign(hamon::declval<K>(), hamon::declval<M>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_insert_or_assign_invocable<Map1&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map2&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map3&, int, T>::value, "");
	static_assert( is_insert_or_assign_invocable<Map4&, int, T>::value, "");

	static_assert(!is_insert_or_assign_invocable<Map1 const&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map2 const&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map3 const&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map4 const&, int, T>::value, "");

	using Map = Map4;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<int>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<int>(), hamon::declval<T>())), "");

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	VERIFY(v.size() == 2);
	VERIFY(v.load_factor() <= v.max_load_factor());
	VERIFY(v[1] == T{10});
	VERIFY(v[3] == T{20});

	{
		auto r = v.insert_or_assign(1, T{30});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == T{30});
		VERIFY(v[3] == T{20});
	}
	{
		auto r = v.insert_or_assign(2, T{40});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{40});
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == T{30});
		VERIFY(v[2] == T{40});
		VERIFY(v[3] == T{20});
	}
	{
		int const k{3};
		auto r = v.insert_or_assign(k, T{50});
		VERIFY(r.first->first == Key{3});
		VERIFY(r.first->second == T{50});
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == T{30});
		VERIFY(v[2] == T{40});
		VERIFY(v[3] == T{50});
	}
	{
		int const k{0};
		auto r = v.insert_or_assign(k, T{60});
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[0] == T{60});
		VERIFY(v[1] == T{30});
		VERIFY(v[2] == T{40});
		VERIFY(v[3] == T{50});
	}

	for (int i = 0; i < 100; ++i)
	{
		auto r = v.insert_or_assign(i + 10, T{42});
		VERIFY(r.first->first == static_cast<Key>(i + 10));
		VERIFY(r.first->second == T{42});
		VERIFY(r.second == true);

		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, InsertOrAssignHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
