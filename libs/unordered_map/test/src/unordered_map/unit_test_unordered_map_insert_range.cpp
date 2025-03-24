/**
 *	@file	unit_test_unordered_map_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr void insert_range(R&& rg);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_unordered_map_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class RangeWrapper>
UNORDERED_MAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::unordered_map<Key, T>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_range(hamon::declval<Range>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_range(hamon::declval<Range>())), "");

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
		VERIFY(v.load_factor() <= v.max_load_factor());
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
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[0] == 90);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 80);
	}
	{
		ValueType a[] =
		{
			{Key{10}, T{13}},
			{Key{11}, T{13}},
			{Key{12}, T{13}},
			{Key{13}, T{13}},
			{Key{14}, T{13}},
			{Key{15}, T{13}},
			{Key{16}, T{13}},
			{Key{17}, T{13}},
			{Key{18}, T{13}},
			{Key{19}, T{13}},
			{Key{20}, T{13}},
			{Key{21}, T{13}},
			{Key{22}, T{13}},
			{Key{23}, T{13}},
			{Key{24}, T{13}},
			{Key{25}, T{13}},
			{Key{26}, T{13}},
			{Key{27}, T{13}},
			{Key{28}, T{13}},
			{Key{29}, T{13}},
			{Key{30}, T{13}},
			{Key{31}, T{13}},
			{Key{32}, T{13}},
			{Key{33}, T{13}},
			{Key{34}, T{13}},
			{Key{35}, T{13}},
			{Key{36}, T{13}},
			{Key{37}, T{13}},
			{Key{38}, T{13}},
			{Key{39}, T{13}},
		};
		v.insert_range(Range(a));
		VERIFY(v.size() == 35);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[0] == 90);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 80);
		VERIFY(v[10] == 13);
		VERIFY(v[11] == 13);
		VERIFY(v[12] == 13);
		VERIFY(v[13] == 13);
		VERIFY(v[14] == 13);
		VERIFY(v[15] == 13);
		VERIFY(v[16] == 13);
		VERIFY(v[17] == 13);
		VERIFY(v[18] == 13);
		VERIFY(v[19] == 13);
		VERIFY(v[20] == 13);
		VERIFY(v[21] == 13);
		VERIFY(v[22] == 13);
		VERIFY(v[23] == 13);
		VERIFY(v[24] == 13);
		VERIFY(v[25] == 13);
		VERIFY(v[26] == 13);
		VERIFY(v[27] == 13);
		VERIFY(v[28] == 13);
		VERIFY(v[29] == 13);
		VERIFY(v[30] == 13);
		VERIFY(v[31] == 13);
		VERIFY(v[32] == 13);
		VERIFY(v[33] == 13);
		VERIFY(v[34] == 13);
		VERIFY(v[35] == 13);
		VERIFY(v[36] == 13);
		VERIFY(v[37] == 13);
		VERIFY(v[38] == 13);
		VERIFY(v[39] == 13);
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
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

GTEST_TEST(UnorderedMapTest, InsertRangeTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::unordered_map<int, ThrowOnCopyIfNegative>;
		using ValueType = typename Map::value_type;

		Map v;
		EXPECT_EQ(0u, v.size());

		{
			ValueType a[] =
			{
				{ 3, ThrowOnCopyIfNegative{ 10}},
				{ 1, ThrowOnCopyIfNegative{ 20}},
				{ 4, ThrowOnCopyIfNegative{-30}},
				{ 1, ThrowOnCopyIfNegative{ 40}},
			};
			// { 4, ThrowOnCopyIfNegative{-30}} をコピーするときに例外を投げる
			EXPECT_THROW(v.insert_range(a), ThrowOnCopyIfNegative::Exception);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(v.at(1).value, 20);
		EXPECT_EQ(v.at(3).value, 10);

		{
			ValueType a[] =
			{
				{ 1, ThrowOnCopyIfNegative{ 50}},
				{ 2, ThrowOnCopyIfNegative{ 60}},
				{ 3, ThrowOnCopyIfNegative{-70}},
				{ 0, ThrowOnCopyIfNegative{ 80}},
			};
			// { 3, ThrowOnCopyIfNegative{-70}} は挿入されないので例外を投げない
			EXPECT_NO_THROW(v.insert_range(a));
		}
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(v.at(0).value, 80);
		EXPECT_EQ(v.at(1).value, 20);
		EXPECT_EQ(v.at(2).value, 60);
		EXPECT_EQ(v.at(3).value, 10);
	}
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_unordered_map_test

#endif
