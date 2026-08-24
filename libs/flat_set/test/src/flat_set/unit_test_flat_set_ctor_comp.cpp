/**
 *	@file	unit_test_flat_set_ctor_comp.cpp
 *
 *	@brief	key_compare を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit flat_set(const key_compare& comp);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace ctor_comp_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;

	static_assert( hamon::is_constructible<Set, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Compare const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Compare const&>::value, "");

	{
		Compare const comp;
		Set v{comp};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}
	{
		TestLess<Key> const comp{42};
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v{comp};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.key_comp() == comp);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, CtorCompTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));
}

}	// namespace ctor_comp_test

}	// namespace hamon_flat_set_test
