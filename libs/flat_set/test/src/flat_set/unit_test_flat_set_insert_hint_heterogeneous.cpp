/**
 *	@file	unit_test_flat_set_insert_hint_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class K> constexpr iterator insert(const_iterator hint, K&& x);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <array>
#include <string>
#include <tuple>
#include <utility>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace insert_hint_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename...> class TKeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Compare = hamon::less<>;
	using KeyContainer = TKeyContainer<Key>;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ConstIterator>(), hamon::declval<int>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ConstIterator>(), hamon::declval<int>())), "");

	{
		Set v;
		VERIFY(check_invariant(v));
		{
			auto r = v.insert(v.end(), 1);
			VERIFY(r->value == 1);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 1);
		VERIFY(v.count(2) == 0);
		{
			auto r = v.insert(v.end(), 2);
			VERIFY(r->value == 2);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 1);
		VERIFY(v.count(2) == 1);
		{
			auto r = v.insert(v.end(), 1);
			VERIFY(r->value == 1);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v.count(0) == 0);
		VERIFY(v.count(1) == 1);
		VERIFY(v.count(2) == 1);
	}

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = TransparentKey;
	using Comp = hamon::less<>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;

		int throw_after = INT_MAX;

		KeyContainer a(ThrowAllocator<Key>{&throw_after});
		Set v(hamon::sorted_unique, hamon::move(a));

		throw_after = 1;

		EXPECT_THROW(v.insert(v.end(), 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_unique, hamon::move(a));

		EXPECT_THROW(v.insert(v.end(), 5), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, InsertHintHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace insert_hint_heterogeneous_test

}	// namespace hamon_flat_set_test
