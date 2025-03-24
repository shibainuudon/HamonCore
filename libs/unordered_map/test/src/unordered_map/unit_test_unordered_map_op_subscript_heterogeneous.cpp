/**
 *	@file	unit_test_unordered_map_op_subscript_heterogeneous.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	template<class K> constexpr mapped_type& operator[](K&& k);
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

namespace op_subscript_heterogeneous_test
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
struct is_op_subscript_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_op_subscript_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>()[hamon::declval<K>()])>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_op_subscript_invocable<Map1&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map2&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map3&, int>::value, "");
	static_assert( is_op_subscript_invocable<Map4&, int>::value, "");

	static_assert(!is_op_subscript_invocable<Map1 const&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map2 const&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map3 const&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map4 const&, int>::value, "");

	using Map = Map4;
	using MappedType = typename Map::mapped_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<int>()]), MappedType&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<int>()]), "");

	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
		};

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == T{10});
		VERIFY(v[3] == T{20});

		v[2] = T{30};

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{30});
		VERIFY(v[3] == T{20});

		{
			int const k{1};
			v[k] = T{40};
		}

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == T{40});
		VERIFY(v[2] == T{30});
		VERIFY(v[3] == T{20});

		for (int i = 0; i < 100; ++i)
		{
			v[i] = T{42};
			VERIFY(v.load_factor() <= v.max_load_factor());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, OpSubscriptHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace op_subscript_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
