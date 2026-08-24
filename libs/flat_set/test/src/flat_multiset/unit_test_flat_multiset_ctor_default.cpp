/**
 *	@file	unit_test_flat_multiset_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr flat_multiset();
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

	static_assert( hamon::is_default_constructible<Set>::value, "");
	//static_assert( hamon::is_nothrow_default_constructible<Set>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<Set>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Set>::value, "");

	{
		Set v;
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}
	{
		Set v{};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}
	{
		Set v = {};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));
}

}	// namespace ctor_default_test

}	// namespace hamon_flat_multiset_test
