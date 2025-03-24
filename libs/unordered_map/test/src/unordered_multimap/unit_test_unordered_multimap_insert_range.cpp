/**
 *	@file	unit_test_unordered_multimap_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr void insert_range(R&& rg);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_unordered_multimap_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class RangeWrapper>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_range(hamon::declval<Range>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_range(hamon::declval<Range>())), "");

#if 0
	Map v;
	{
		ValueType a[] =
		{
			{Key{3}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		Range r(a);
		v.insert_range(r);
		VERIFY(v.size() == 3);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
	}
	{
		ValueType a[] =
		{
			{Key{2}, T{70}},
			{Key{4}, T{80}},
			{Key{0}, T{90}},
			{Key{1}, T{40}},
		};
		v.insert_range(Range(a));
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 90);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 80);
	}
#endif

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, T, test_input_range>() &&
		test_impl<Key, T, test_forward_range>() &&
		test_impl<Key, T, test_bidirectional_range>() &&
		test_impl<Key, T, test_random_access_range>() &&
		test_impl<Key, T, test_contiguous_range>() &&
		test_impl<Key, T, test_input_sized_range>() &&
		test_impl<Key, T, test_forward_sized_range>() &&
		test_impl<Key, T, test_bidirectional_sized_range>() &&
		test_impl<Key, T, test_random_access_sized_range>() &&
		test_impl<Key, T, test_contiguous_sized_range>();
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertRangeTest)
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
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_unordered_multimap_test

#endif
