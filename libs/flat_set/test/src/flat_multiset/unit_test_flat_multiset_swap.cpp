/**
 *	@file	unit_test_flat_multiset_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(flat_multiset&) noexcept;
 *	constexpr friend void swap(flat_multiset& x, flat_multiset& y) noexcept;
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

namespace swap_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Compare = TestLess<Key>;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().swap(hamon::declval<Set&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), void>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().swap(hamon::declval<Set&>())), "");
	static_assert(noexcept(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), "");

	Compare c1{4};
	Compare c2{5};
	Set v1
	{
		{
			Key{2},
			Key{3},
			Key{3},
		},
		c1
	};

	Set v2
	{
		{
			Key{1},
			Key{2},
			Key{1},
			Key{3},
		},
		c2
	};

	v1.swap(v2);

	VERIFY(check_invariant(v1));
	VERIFY(v1.size() == 4);
	VERIFY(v1.key_comp() == c2);
	VERIFY(v1.count(Key{1}) == 2);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(check_invariant(v2));
	VERIFY(v2.size() == 3);
	VERIFY(v2.key_comp() == c1);
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 2);

	swap(v1, v2);

	VERIFY(check_invariant(v1));
	VERIFY(v1.size() == 3);
	VERIFY(v1.key_comp() == c1);
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 2);
	VERIFY(check_invariant(v2));
	VERIFY(v2.size() == 4);
	VERIFY(v2.key_comp() == c2);
	VERIFY(v2.count(Key{1}) == 2);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, SwapTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_flat_multiset_test
