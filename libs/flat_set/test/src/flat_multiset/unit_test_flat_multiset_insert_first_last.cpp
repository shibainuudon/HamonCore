/**
 *	@file	unit_test_flat_multiset_insert_first_last.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator>
 *	constexpr void insert(InputIterator first, InputIterator last);
 *
 *	template<class InputIterator>
 *	constexpr void insert(sorted_equivalent_t, InputIterator first, InputIterator last);
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/deque.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace insert_first_last_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare, template <typename> class IteratorWrapper>
FLAT_SET_TEST_CONSTEXPR bool test_impl()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::sorted_equivalent, hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::sorted_equivalent, hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

	{
		Set v;
		VERIFY(check_invariant(v));
		{
			ValueType a[] =
			{
				Key{1},
				Key{1},
				Key{3},
				Key{2},
			};
			v.insert(InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		{
			ValueType a[] =
			{
				Key{5},
				Key{1},
				Key{2},
				Key{1},
				Key{4},
				Key{4},
			};
			v.insert(InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 10);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 4);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		Set v;
		{
			ValueType a[] =
			{
				Key{1},
				Key{3},
				Key{2},
			};
			hamon::ranges::sort(a, v.value_comp());
			v.insert(hamon::sorted_equivalent, InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)});
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
				Key{5},
				Key{1},
				Key{2},
				Key{4},
			};
			hamon::ranges::sort(a, v.value_comp());
			v.insert(hamon::sorted_equivalent, InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)});
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

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<KeyContainer, Compare, cpp17_input_iterator_wrapper>());
//	VERIFY(test_impl<KeyContainer, Compare, input_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, Compare, forward_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, Compare, bidirectional_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, Compare, random_access_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, Compare, contiguous_iterator_wrapper>());

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		int throw_after = INT_MAX;

		KeyContainer a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		Set v(hamon::sorted_equivalent, hamon::move(a));

		throw_after = 1;

		ValueType x[] =
		{
			Key{11},
			Key{13},
			Key{12},
			Key{15},
			Key{16},
			Key{17},
		};
		EXPECT_THROW(v.insert(hamon::ranges::begin(x), hamon::ranges::end(x)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;
		using ValueType = typename Set::value_type;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		ValueType x[] =
		{
			Key{11},
			Key{13},
			Key{12},
			Key{15},
			Key{16},
			Key{17},
		};
		EXPECT_THROW(v.insert(hamon::ranges::begin(x), hamon::ranges::end(x)), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, InsertFirstLastTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<char>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace insert_first_last_test

}	// namespace hamon_flat_multiset_test
