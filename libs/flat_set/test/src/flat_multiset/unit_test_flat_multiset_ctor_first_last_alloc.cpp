/**
 *	@file	unit_test_flat_multiset_ctor_first_last_alloc.cpp
 *
 *	@brief	first と last とアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multiset(InputIterator first, InputIterator last, const Alloc& a);
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multiset(InputIterator first, InputIterator last, const key_compare& comp, const Alloc& a);
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multiset(sorted_equivalent_t, InputIterator first, InputIterator last, const Alloc& a);
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multiset(sorted_equivalent_t, InputIterator first, InputIterator last, const key_compare& comp, const Alloc& a);
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace ctor_first_last_alloc_test
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
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Set, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Set, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Set, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	{
		ValueType a[] =
		{
			{Key{1}},
			{Key{3}},
			{Key{1}},
			{Key{3}},
			{Key{2}},
			{Key{3}},
		};
		Alloc const alloc;
		Set v{InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)}, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		ValueType a[] =
		{
			{Key{1}},
			{Key{3}},
			{Key{2}},
			{Key{2}},
			{Key{2}},
			{Key{1}},
		};
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_multiset<Key, TestLess<Key>, KeyContainer> v{InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)}, comp, alloc};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(it == v.end());
	}
	{
		ValueType a[] =
		{
			Key{1},
			Key{3},
			Key{2},
			Key{2},
		};
		hamon::ranges::sort(a, Set{}.value_comp());
		Alloc const alloc;
		Set v{hamon::sorted_equivalent, InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)}, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		ValueType a[] =
		{
			Key{0},
			Key{0},
			Key{1},
			Key{3},
			Key{4},
		};
		TestLess<Key> const comp{43};
		Alloc const alloc;
		hamon::flat_multiset<Key, TestLess<Key>, KeyContainer> v{hamon::sorted_equivalent, InputIterator{hamon::ranges::begin(a)}, InputIterator{hamon::ranges::end(a)}, comp, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{0});
		++it;
		VERIFY(*it == Key{0});
		++it;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(*it == Key{4});
		++it;
		VERIFY(it == v.end());
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

GTEST_TEST(FlatMultisetTest, CtorFirstLastAllocTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_first_last_alloc_test

}	// namespace hamon_flat_multiset_test
