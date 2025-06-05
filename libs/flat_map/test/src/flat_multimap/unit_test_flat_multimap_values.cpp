/**
 *	@file	unit_test_flat_multimap_values.cpp
 *
 *	@brief	values のテスト
 *
 *	constexpr const mapped_container_type& values() const noexcept;
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
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

namespace values_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;

	{
		using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().values()), MappedContainer const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().values()), MappedContainer const&>::value, "");
		static_assert(noexcept(hamon::declval<Map&      >().values()), "");
		static_assert(noexcept(hamon::declval<Map const&>().values()), "");

		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
		};
		auto const& x = v.values();
		VERIFY(x.size() == 3);
		T const expected[] = {T{30}, T{10}, T{20}};
		VERIFY(hamon::ranges::equal(x, expected));
	}
	{
		using Map = hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&      >().values()), MappedContainer const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().values()), MappedContainer const&>::value, "");
		static_assert(noexcept(hamon::declval<Map&      >().values()), "");
		static_assert(noexcept(hamon::declval<Map const&>().values()), "");

		Map const v
		{
			{Key{3}, T{10}},
			{Key{4}, T{20}},
			{Key{1}, T{30}},
			{Key{2}, T{40}},
		};
		auto const& x = v.values();
		VERIFY(x.size() == 4);
		T const expected[] = {T{20}, T{10}, T{40}, T{30}};
		VERIFY(hamon::ranges::equal(x, expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, ValuesTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace values_test

}	// namespace hamon_flat_multimap_test
