/**
 *	@file	unit_test_unordered_map_at_heterogeneous.cpp
 *
 *	@brief	at のテスト
 *
 *	template<class K> constexpr mapped_type& at(const K& k);
 *	template<class K> constexpr const mapped_type& at(const K& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
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

namespace at_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_at_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_at_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().at(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_at_invocable<Map1&, int>::value, "");
	static_assert(!is_at_invocable<Map2&, int>::value, "");
	static_assert(!is_at_invocable<Map3&, int>::value, "");
	static_assert( is_at_invocable<Map4&, int>::value, "");

	static_assert(!is_at_invocable<Map1 const&, int>::value, "");
	static_assert(!is_at_invocable<Map2 const&, int>::value, "");
	static_assert(!is_at_invocable<Map3 const&, int>::value, "");
	static_assert( is_at_invocable<Map4 const&, int>::value, "");

	using Map = Map4;
	using MappedType = typename Map::mapped_type;
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().at(hamon::declval<int>())), MappedType&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().at(hamon::declval<int>())), MappedType const&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().at(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().at(hamon::declval<int>())), "");

	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
		};

		VERIFY(v.at(1) == T{20});
		VERIFY(v.at(2) == T{10});
		VERIFY(v.at(3) == T{30});

		v.at(3) = T{40};

		VERIFY(v.at(1) == T{20});
		VERIFY(v.at(2) == T{10});
		VERIFY(v.at(3) == T{40});
	}
	{
		Map const v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(v.at(1) == T{20});
		VERIFY(v.at(3) == T{10});
		VERIFY(v.at(4) == T{30});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, AtHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4834)	// 'nodiscard' 属性を持つ関数の戻り値を破棄しています
HAMON_WARNING_DISABLE_CLANG("-Wunused-result")
HAMON_WARNING_DISABLE_GCC("-Wunused-result")
	{
		using Key = TransparentKey;
		hamon::unordered_map<Key, float, TransparentHash, hamon::equal_to<>> v
		{
			{ Key{1}, 0.5f },
			{ Key{7}, 1.5f },
			{ Key{3}, 2.5f },
		};

		EXPECT_THROW   (v.at(0), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(1));
		EXPECT_THROW   (v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(3));

		v[0] = 3.5f;

		EXPECT_NO_THROW(v.at(0));
		EXPECT_NO_THROW(v.at(1));
		EXPECT_THROW   (v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(3));
	}
	{
		using Key = TransparentKey;
		hamon::unordered_map<Key, float, TransparentHash, hamon::equal_to<>> const v
		{
			{ Key{2}, 0.5f },
			{ Key{0}, 1.5f },
			{ Key{3}, 2.5f },
		};

		EXPECT_NO_THROW(v.at(0));
		EXPECT_THROW   (v.at(1), hamon::out_of_range);
		EXPECT_NO_THROW(v.at(2));
		EXPECT_NO_THROW(v.at(3));
	}
HAMON_WARNING_POP()
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace at_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
