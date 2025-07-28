/**
 *	@file	unit_test_flat_multiset_insert_init_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr void insert(initializer_list<value_type> il);
 *	constexpr void insert(sorted_equivalent_t, initializer_list<value_type> il);
 */

#include <hamon/flat_set/flat_multiset.hpp>
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
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace insert_init_list_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::sorted_equivalent, hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<std::initializer_list<ValueType>>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::sorted_equivalent, hamon::declval<std::initializer_list<ValueType>>())), "");

	{
		Set v;
		VERIFY(check_invariant(v));

		v.insert({
			Key{1},
			Key{3},
			Key{1},
			Key{2},
		});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);

		v.insert({
			Key{2},
			Key{5},
			Key{1},
			Key{2},
			Key{4},
			Key{4},
		});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 10);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 3);
		VERIFY(v.count(Key{2}) == 3);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer> v;
		VERIFY(check_invariant(v));

		v.insert(hamon::sorted_equivalent, {
			Key{1},
			Key{2},
			Key{3},
		});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);

		v.insert(hamon::sorted_equivalent, {
			Key{1},
			Key{4},
			Key{5},
		});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer> v;
		VERIFY(check_invariant(v));

		v.insert(hamon::sorted_equivalent, {
			Key{4},
			Key{2},
			Key{1},
		});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 0);

		v.insert(hamon::sorted_equivalent, {
			Key{5},
			Key{4},
			Key{3},
			Key{2},
			Key{1},
			Key{0},
		});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 9);
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
	}

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

		int throw_after = INT_MAX;

		KeyContainer a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		Set v(hamon::sorted_equivalent, hamon::move(a));

		throw_after = 1;

		EXPECT_THROW(v.insert({
			Key{11},
			Key{13},
			Key{12},
			Key{15},
			Key{16},
			Key{17},
		}), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		EXPECT_THROW(v.insert(hamon::sorted_equivalent, {
			Key{11},
			Key{12},
			Key{13},
			Key{15},
			Key{16},
			Key{17},
		}), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, InsertInitListTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::less<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace insert_init_list_test

}	// namespace hamon_flat_multiset_test
