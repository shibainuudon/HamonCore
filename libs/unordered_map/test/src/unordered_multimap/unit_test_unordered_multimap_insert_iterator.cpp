/**
 *	@file	unit_test_unordered_multimap_insert_iterator.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator> constexpr void insert(InputIterator first, InputIterator last);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace insert_iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, template <typename> class IteratorWrapper>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using ValueType = typename Map::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

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
		v.insert(InputIterator{a}, InputIterator{a + 6});
		VERIFY(v.size() == 6);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		ValueType a[] =
		{
			{Key{2}, T{70}},
			{Key{4}, T{80}},
			{Key{0}, T{90}},
			{Key{1}, T{40}},
		};
		v.insert(InputIterator{a}, InputIterator{a + 4});
		VERIFY(v.size() == 10);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 3);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 1);
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
		v.insert(InputIterator{a}, InputIterator{a + 30});
		VERIFY(v.size() == 40);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	return
		test_impl<Key, T, cpp17_input_iterator_wrapper>() &&
		//test_impl<Key, T, input_iterator_wrapper>() &&
		test_impl<Key, T, forward_iterator_wrapper>() &&
		test_impl<Key, T, bidirectional_iterator_wrapper>() &&
		test_impl<Key, T, random_access_iterator_wrapper>() &&
		test_impl<Key, T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertIteratorTest)
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

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::unordered_multimap<int, ThrowOnCopyIfNegative>;
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
			EXPECT_THROW(v.insert(a, a + 4), ThrowOnCopyIfNegative::Exception);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(0u, v.count(0));
		EXPECT_EQ(1u, v.count(1));
		EXPECT_EQ(0u, v.count(2));
		EXPECT_EQ(1u, v.count(3));
		EXPECT_EQ(0u, v.count(4));

		{
			ValueType a[] =
			{
				{ 1, ThrowOnCopyIfNegative{ 50}},
				{ 2, ThrowOnCopyIfNegative{ 60}},
				{ 3, ThrowOnCopyIfNegative{-70}},
				{ 0, ThrowOnCopyIfNegative{ 80}},
			};
			// { 3, ThrowOnCopyIfNegative{-70}} をコピーするときに例外を投げる
			EXPECT_THROW(v.insert(a, a + 4), ThrowOnCopyIfNegative::Exception);
		}
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(0u, v.count(0));
		EXPECT_EQ(2u, v.count(1));
		EXPECT_EQ(1u, v.count(2));
		EXPECT_EQ(1u, v.count(3));
		EXPECT_EQ(0u, v.count(4));
	}
#endif
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_iterator_test

}	// namespace hamon_unordered_multimap_test
