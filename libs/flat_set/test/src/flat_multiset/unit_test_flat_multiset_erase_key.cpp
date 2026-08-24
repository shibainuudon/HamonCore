/**
 *	@file	unit_test_flat_multiset_erase_key.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr size_type erase(const key_type& x);
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

namespace erase_key_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");

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
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 2);
	VERIFY(v.count(Key{3}) == 3);

	VERIFY(v.erase(Key{0}) == 0);

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 6);
	VERIFY(!v.empty());
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 2);
	VERIFY(v.count(Key{3}) == 3);

	VERIFY(v.erase(Key{1}) == 1);

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 5);
	VERIFY(!v.empty());
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 2);
	VERIFY(v.count(Key{3}) == 3);

	VERIFY(v.erase(Key{2}) == 2);

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(!v.empty());
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 3);

	VERIFY(v.erase(Key{3}) == 3);

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 0);
	VERIFY(v.empty());
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);

	VERIFY(v.erase(Key{4}) == 0);

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 0);
	VERIFY(v.empty());
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);

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
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		EXPECT_THROW(v.erase(Key{1}), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, EraseKeyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<float>, hamon::less<float>>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

}	// namespace erase_key_test

}	// namespace hamon_flat_multiset_test
