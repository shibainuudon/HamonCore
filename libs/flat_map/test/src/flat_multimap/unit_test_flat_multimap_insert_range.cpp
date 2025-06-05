/**
 *	@file	unit_test_flat_multimap_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr void insert_range(R&& rg);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace insert_range_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare, template <typename> class RangeWrapper>
FLAT_MAP_TEST_CONSTEXPR bool test_impl()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_range(hamon::declval<Range const&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_range(hamon::declval<Range&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_range(hamon::declval<Range&&>())), "");

	{
		Map v;
		{
			ValueType a[] =
			{
				{Key{1}, T{10}},
				{Key{3}, T{20}},
				{Key{2}, T{30}},
			};
			Range r(a);
			v.insert_range(r);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		{
			ValueType a[] =
			{
				{Key{5}, T{40}},
				{Key{1}, T{50}},
				{Key{2}, T{60}},
				{Key{4}, T{70}},
			};
			v.insert_range(Range(a));
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_input_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_forward_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_bidirectional_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_random_access_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_contiguous_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_input_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_forward_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_bidirectional_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_random_access_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_contiguous_sized_range>());

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		ValueType x[] =
		{
			{Key{11}, T{10}},
			{Key{13}, T{20}},
			{Key{12}, T{30}},
			{Key{15}, T{40}},
			{Key{16}, T{50}},
			{Key{17}, T{60}},
		};
		EXPECT_THROW(v.insert_range(x), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		ValueType x[] =
		{
			{Key{11}, T{10}},
			{Key{12}, T{20}},
			{Key{13}, T{30}},
			{Key{15}, T{40}},
			{Key{16}, T{50}},
			{Key{17}, T{60}},
		};
		EXPECT_THROW(v.insert_range(x), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		ValueType x[] =
		{
			{Key{11}, T{10}},
			{Key{13}, T{20}},
			{Key{12}, T{30}},
			{Key{15}, T{40}},
			{Key{16}, T{50}},
			{Key{17}, T{60}},
		};
		EXPECT_THROW(v.insert_range(x), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		ValueType x[] =
		{
			{Key{11}, T{10}},
			{Key{13}, T{20}},
			{Key{12}, T{30}},
			{Key{15}, T{40}},
			{Key{16}, T{50}},
			{Key{17}, T{60}},
		};
		EXPECT_THROW(v.insert_range(x), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		ValueType x[] =
		{
			{Key{11}, T{10}},
			{Key{13}, T{20}},
			{Key{12}, T{30}},
			{Key{15}, T{40}},
			{Key{16}, T{50}},
			{Key{17}, T{60}},
		};
		EXPECT_THROW(v.insert_range(x), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		ValueType x[] =
		{
			{Key{11}, T{10}},
			{Key{12}, T{20}},
			{Key{13}, T{30}},
			{Key{15}, T{40}},
			{Key{16}, T{50}},
			{Key{17}, T{60}},
		};
		EXPECT_THROW(v.insert_range(x), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultimapTest, InsertRangeTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		hamon::flat_multimap<int, char> fm =
		{
			{3, 'a'}
		};

		hamon::flat_multimap<int, char> fm2 =
		{
			{ 5, 'd'},
			{15, 'e'},
			{ 3, 'h'},
		};

		fm.insert_range(fm2);

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":" << p.second << ", ";
		}
		EXPECT_EQ("3:a, 3:h, 5:d, 15:e, ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_range_test

}	// namespace hamon_flat_multimap_test
