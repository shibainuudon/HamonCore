/**
 *	@file	unit_test_flat_multiset_key_comp.cpp
 *
 *	@brief	key_comp のテスト
 *
 *	constexpr key_compare key_comp() const;
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

namespace key_comp_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Compare = TestLess<Key>;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&      >().key_comp()), Compare>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().key_comp()), Compare>::value, "");
	static_assert(!noexcept(hamon::declval<Set&      >().key_comp()), "");
	static_assert(!noexcept(hamon::declval<Set const&>().key_comp()), "");

	{
		Compare c1{4};
		Compare c2{5};
		Set v{c1};
		VERIFY(v.key_comp() == c1);
		VERIFY(v.key_comp() != c2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, KeyCompTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>>()));
}

}	// namespace key_comp_test

}	// namespace hamon_flat_multiset_test
