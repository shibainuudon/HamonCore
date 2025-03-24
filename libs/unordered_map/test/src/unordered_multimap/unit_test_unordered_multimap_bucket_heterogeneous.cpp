/**
 *	@file	unit_test_unordered_multimap_bucket_heterogeneous.cpp
 *
 *	@brief	bucket のテスト
 *
 *	template<class K> constexpr size_type bucket(const K& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_unordered_multimap_test
{

namespace bucket_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_bucket_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_bucket_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().bucket(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_multimap<Key, T>;
	using Map2 = hamon::unordered_multimap<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_multimap<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_multimap<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_bucket_invocable<Map1&, int>::value, "");
	static_assert(!is_bucket_invocable<Map2&, int>::value, "");
	static_assert(!is_bucket_invocable<Map3&, int>::value, "");
	static_assert( is_bucket_invocable<Map4&, int>::value, "");

	static_assert(!is_bucket_invocable<Map1 const&, int>::value, "");
	static_assert(!is_bucket_invocable<Map2 const&, int>::value, "");
	static_assert(!is_bucket_invocable<Map3 const&, int>::value, "");
	static_assert( is_bucket_invocable<Map4 const&, int>::value, "");

	using Map = Map4;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().bucket(hamon::declval<int>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().bucket(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<int>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<int>())), "");
#endif

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};
	VERIFY(v.bucket(0) < v.bucket_count());
	VERIFY(v.bucket(1) < v.bucket_count());
	VERIFY(v.bucket(2) < v.bucket_count());
	VERIFY(v.bucket(3) < v.bucket_count());
	VERIFY(v.bucket(4) < v.bucket_count());
	VERIFY(v.bucket(5) < v.bucket_count());
	VERIFY(v.bucket(100) < v.bucket_count());

	return true;
}

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	using Key = TransparentKey;
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().bucket(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().bucket(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().bucket(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().bucket(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, BucketHeterogeneousTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<int>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<char>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<float>());
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace bucket_heterogeneous_test

}	// namespace hamon_unordered_multimap_test

#endif
