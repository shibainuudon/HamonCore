/**
 *	@file	unit_test_unordered_map_try_emplace_heterogeneous.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class K, class... Args>
 *	constexpr pair<iterator, bool> try_emplace(K&& k, Args&&... args);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
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

namespace try_emplace_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename T, typename = void>
struct is_try_emplace_invocable
	: public hamon::false_type {};

template <typename Map, typename K, typename T>
struct is_try_emplace_invocable<Map, K, T, hamon::void_t<decltype(hamon::declval<Map>().try_emplace(hamon::declval<K>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_try_emplace_invocable<Map1&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map2&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map3&, int, T>::value, "");
	static_assert( is_try_emplace_invocable<Map4&, int, T>::value, "");

	static_assert(!is_try_emplace_invocable<Map1 const&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map2 const&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map3 const&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map4 const&, int, T>::value, "");

	using Map = Map4;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<int const&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<int&&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<int const&>(), hamon::declval<T>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<int&&>(), hamon::declval<T>())), "");

	Map v;

	{
		auto r = v.try_emplace(3, T{10});
		VERIFY(r.first->first == Key{3});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[3] == T{10});
	}
	{
		int k = 2;
		auto r = v.try_emplace(k, T{20});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{20});
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[2] == T{20});
		VERIFY(v[3] == T{10});
	}
	{
		auto r = v.try_emplace(2, T{30});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{20});
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[2] == T{20});
		VERIFY(v[3] == T{10});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, TryEmplaceHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Key = TransparentKey;
		hamon::unordered_map<Key, ThrowIfNegative, TransparentHash, hamon::equal_to<>> v;
		EXPECT_TRUE(v.empty());

		EXPECT_THROW(v.try_emplace(1, -1), ThrowIfNegative::Exception);
		EXPECT_EQ(0u, v.size());

		v.try_emplace(1, 10);
		EXPECT_EQ(1u, v.size());

		// 要素が挿入されないときは一時オブジェクトは作成されない
		EXPECT_NO_THROW(v.try_emplace(1, -1));
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.try_emplace(2, -10), ThrowIfNegative::Exception);
		EXPECT_EQ(1u, v.size());

		EXPECT_THROW(v.try_emplace(3, -20), ThrowIfNegative::Exception);
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

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace try_emplace_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
