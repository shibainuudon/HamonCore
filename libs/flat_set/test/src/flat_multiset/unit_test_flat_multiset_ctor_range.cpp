/**
 *	@file	unit_test_flat_multiset_ctor_range.cpp
 *
 *	@brief	Range を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr flat_multiset(from_range_t, R&& rg);
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr flat_multiset(from_range_t, R&& rg, const key_compare& comp);
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace ctor_range_test
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
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range&&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::from_range_t, Range&&, Compare const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range&&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::from_range_t, Range&&, Compare const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range&&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::from_range_t, Range&&, Compare const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range&&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::from_range_t, Range&&, Compare const&>::value, "");

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
		Set v{hamon::from_range, r};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 3);
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
		Set v{hamon::from_range, Range{a}};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 8);
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 3);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
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
		hamon::flat_multiset<Key, TestLess<Key>, KeyContainer> v{hamon::from_range, r, comp};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(*it == Key{3});
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

GTEST_TEST(FlatMultisetTest, CtorRangeTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_range_test

}	// namespace hamon_flat_multiset_test
