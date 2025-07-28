/**
 *	@file	unit_test_flat_set_ctor_range_alloc.cpp
 *
 *	@brief	Range とアロケータを引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R, class Alloc>
 *	constexpr flat_set(from_range_t, R&& rg, const Alloc& a);
 *
 *	template<container-compatible-range<value_type> R, class Alloc>
 *	constexpr flat_set(from_range_t, R&& rg, const key_compare& comp, const Alloc& a);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace ctor_range_alloc_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare, template <typename> class RangeWrapper>
FLAT_SET_TEST_CONSTEXPR bool test_impl()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range&&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range const&, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range&&, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range&&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range const&, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range&&, Compare const&, Alloc const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range&&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range const&, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range&&, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range&&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range const&, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range&&, Compare const&, Alloc const&>::value, "");

	{
		ValueType a[] =
		{
			{Key{1}},
			{Key{3}},
			{Key{1}},
			{Key{2}},
			{Key{1}},
		};
		Range r(a);
		Alloc const alloc;
		Set v{hamon::from_range, r, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		ValueType a[] =
		{
			{Key{5}},
			{Key{5}},
			{Key{0}},
			{Key{1}},
			{Key{1}},
			{Key{7}},
			{Key{2}},
			{Key{1}},
		};
		Alloc const alloc;
		Set v{hamon::from_range, Range{a}, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 1);
		VERIFY(v.count(Key{6}) == 0);
		VERIFY(v.count(Key{7}) == 1);
	}
	{
		ValueType a[] =
		{
			{Key{3}},
			{Key{1}},
			{Key{3}},
			{Key{2}},
			{Key{3}},
		};
		Range r(a);
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v{hamon::from_range, r, comp, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<KeyContainer, Compare, test_input_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_forward_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_bidirectional_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_random_access_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_contiguous_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_input_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_forward_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_bidirectional_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_random_access_sized_range>());
	VERIFY(test_impl<KeyContainer, Compare, test_contiguous_sized_range>());

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, CtorRangeAllocTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_range_alloc_test

}	// namespace hamon_flat_set_test
