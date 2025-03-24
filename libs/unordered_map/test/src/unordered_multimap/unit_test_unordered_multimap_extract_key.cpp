/**
 *	@file	unit_test_unordered_multimap_extract_key.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr node_type extract(const key_type& x);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multimap_test
{

namespace extract_key_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using NodeType = typename Map::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().extract(hamon::declval<Key const&>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<Key const&>())), "");
#endif

	Map v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
		{Key{4}, T{60}},
		{Key{4}, T{70}},
	};
	VERIFY(v.size() == 7);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 2);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 3);
	VERIFY(v.count(Key{5}) == 1);

	{
		auto r = v.extract(Key{0});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == Key{1});
//		VERIFY(r.mapped() == T{20});
		VERIFY(v.size() == 6);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == Key{1});
//		VERIFY(r.mapped() == T{20});
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{2});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{3});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == Key{3});
//		VERIFY(r.mapped() == T{20});
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{4});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == Key{4});
//		VERIFY(r.mapped() == T{20});
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, ExtractKeyTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace extract_key_test

}	// namespace hamon_unordered_multimap_test

#endif
