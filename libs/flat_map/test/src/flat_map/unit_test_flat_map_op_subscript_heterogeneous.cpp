/**
 *	@file	unit_test_flat_map_op_subscript_heterogeneous.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	template<class K> constexpr mapped_type& operator[](K&& x);
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
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace op_subscript_heterogeneous_test
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
struct is_op_subscript_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_op_subscript_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>()[hamon::declval<K>()])>>
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

	static_assert( is_op_subscript_invocable<Map1&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map2&, int>::value, "");
	static_assert( is_op_subscript_invocable<Map3&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map4&, int>::value, "");

	static_assert(!is_op_subscript_invocable<Map1 const&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map2 const&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map3 const&, int>::value, "");
	static_assert(!is_op_subscript_invocable<Map4 const&, int>::value, "");

	using Map = Map1;
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<Key const&>()]), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>()[hamon::declval<Key&&>()]),      T&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<Key const&>()]), "");
	static_assert(!noexcept(hamon::declval<Map&>()[hamon::declval<Key&&>()]), "");

	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
		};

		VERIFY(v.size() == 2);
		VERIFY(v[1] == T{10});
		VERIFY(v[3] == T{20});

		v[2] = T{30};

		VERIFY(v.size() == 3);
		VERIFY(v[1] == T{10});
		VERIFY(v[2] == T{30});
		VERIFY(v[3] == T{20});

		{
			int const k{1};
			v[k] = T{40};
		}

		VERIFY(v.size() == 3);
		VERIFY(v[1] == T{40});
		VERIFY(v[2] == T{30});
		VERIFY(v[3] == T{20});

		{
			int const k{5};
			v[k] = T{50};
		}

		VERIFY(v.size() == 4);
		VERIFY(v[1] == T{40});
		VERIFY(v[2] == T{30});
		VERIFY(v[3] == T{20});
		VERIFY(v[5] == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, OpSubscriptHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<char>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace op_subscript_heterogeneous_test

}	// namespace hamon_flat_map_test
