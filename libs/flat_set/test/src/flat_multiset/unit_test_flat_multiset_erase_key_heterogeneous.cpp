/**
 *	@file	unit_test_flat_multiset_erase_key_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> constexpr size_type erase(K&& x);
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

namespace erase_key_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Set, typename K, typename = void>
struct is_erase_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_erase_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().erase(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set1 = hamon::flat_multiset<Key, hamon::less<>, KeyContainer>;
	using Set2 = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
	using Set3 = hamon::flat_multiset<Key, hamon::greater<>, KeyContainer>;
	using Set4 = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;

	static_assert( is_erase_invocable<Set1&, int>::value, "");
	static_assert(!is_erase_invocable<Set2&, int>::value, "");
	static_assert( is_erase_invocable<Set3&, int>::value, "");
	static_assert(!is_erase_invocable<Set4&, int>::value, "");

	static_assert(!is_erase_invocable<Set1 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set2 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set3 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set4 const&, int>::value, "");

	{
		using Set = Set1;
		using SizeType = typename Set::size_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<int const&>())), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<int&&>())), SizeType>::value, "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int&&>())), "");

		Set v
		{
			Key{3},
			Key{1},
			Key{3},
			Key{2},
			Key{2},
			Key{3},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(!v.empty());
		VERIFY(v.count(1) == 1);
		VERIFY(v.count(2) == 2);
		VERIFY(v.count(3) == 3);

		VERIFY(v.erase(0) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(!v.empty());
		VERIFY(v.count(1) == 1);
		VERIFY(v.count(2) == 2);
		VERIFY(v.count(3) == 3);

		VERIFY(v.erase(1) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		VERIFY(!v.empty());
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 2);
		VERIFY(v.count(3) == 3);

		VERIFY(v.erase(2) == 2);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 0);
		VERIFY(v.count(3) == 3);

		VERIFY(v.erase(3) == 3);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 0);
		VERIFY(v.count(3) == 0);

		VERIFY(v.erase(4) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
		VERIFY(v.count(1) == 0);
		VERIFY(v.count(2) == 0);
		VERIFY(v.count(3) == 0);
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
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		EXPECT_THROW(v.erase(1), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, EraseKeyHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace erase_key_heterogeneous_test

}	// namespace hamon_flat_multiset_test
