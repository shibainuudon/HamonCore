/**
 *	@file	unit_test_flat_map_upper_bound_heterogeneous.cpp
 *
 *	@brief	upper_bound のテスト
 *
 *	template<class K> constexpr iterator upper_bound(const K& x);
 *	template<class K> constexpr const_iterator upper_bound(const K& x) const;
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

namespace upper_bound_heterogeneous_test
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
struct is_upper_bound_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_upper_bound_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().upper_bound(hamon::declval<K>()))>>
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

	static_assert( is_upper_bound_invocable<Map1&, int>::value, "");
	static_assert(!is_upper_bound_invocable<Map2&, int>::value, "");
	static_assert( is_upper_bound_invocable<Map3&, int>::value, "");
	static_assert(!is_upper_bound_invocable<Map4&, int>::value, "");

	static_assert( is_upper_bound_invocable<Map1 const&, int>::value, "");
	static_assert(!is_upper_bound_invocable<Map2 const&, int>::value, "");
	static_assert( is_upper_bound_invocable<Map3 const&, int>::value, "");
	static_assert(!is_upper_bound_invocable<Map4 const&, int>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<Map1 const&>().upper_bound(hamon::declval<int const&>())), typename Map1::const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().upper_bound(hamon::declval<int const&>())), typename Map1::iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map1 const&>().upper_bound(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().upper_bound(hamon::declval<int const&>())), "");

	{
		Map1 v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.upper_bound(0) == (v.begin() + 0));
		VERIFY(v.upper_bound(1) == (v.begin() + 1));
		VERIFY(v.upper_bound(2) == (v.begin() + 1));
		VERIFY(v.upper_bound(3) == (v.begin() + 2));
		VERIFY(v.upper_bound(4) == (v.begin() + 3));
		VERIFY(v.upper_bound(5) == (v.begin() + 3));
		VERIFY(v.upper_bound(6) == v.end());
		VERIFY(v.upper_bound(7) == v.end());

		auto const& cv = v;
		VERIFY(cv.upper_bound(0) == (cv.begin() + 0));
		VERIFY(cv.upper_bound(1) == (cv.begin() + 1));
		VERIFY(cv.upper_bound(2) == (cv.begin() + 1));
		VERIFY(cv.upper_bound(3) == (cv.begin() + 2));
		VERIFY(cv.upper_bound(4) == (cv.begin() + 3));
		VERIFY(cv.upper_bound(5) == (cv.begin() + 3));
		VERIFY(cv.upper_bound(6) == cv.end());
		VERIFY(cv.upper_bound(7) == cv.end());
	}
	{
		Map3 v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.upper_bound(0) == v.end());
		VERIFY(v.upper_bound(1) == v.end());
		VERIFY(v.upper_bound(2) == (v.begin() + 3));
		VERIFY(v.upper_bound(3) == (v.begin() + 3));
		VERIFY(v.upper_bound(4) == (v.begin() + 2));
		VERIFY(v.upper_bound(5) == (v.begin() + 1));
		VERIFY(v.upper_bound(6) == (v.begin() + 1));
		VERIFY(v.upper_bound(7) == (v.begin() + 0));

		auto const& cv = v;
		VERIFY(cv.upper_bound(0) == cv.end());
		VERIFY(cv.upper_bound(1) == cv.end());
		VERIFY(cv.upper_bound(2) == (cv.begin() + 3));
		VERIFY(cv.upper_bound(3) == (cv.begin() + 3));
		VERIFY(cv.upper_bound(4) == (cv.begin() + 2));
		VERIFY(cv.upper_bound(5) == (cv.begin() + 1));
		VERIFY(cv.upper_bound(6) == (cv.begin() + 1));
		VERIFY(cv.upper_bound(7) == (cv.begin() + 0));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, UpperBoundHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<long>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace upper_bound_heterogeneous_test

}	// namespace hamon_flat_map_test
