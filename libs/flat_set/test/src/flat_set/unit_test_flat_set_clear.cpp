/**
 *	@file	unit_test_flat_set_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	constexpr void clear() noexcept;
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
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().clear()), void>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().clear()), "");

	Set v
	{
		Key{2},
		Key{3},
		Key{1},
	};
	VERIFY(check_invariant(v));
	VERIFY(!v.empty());
	VERIFY(v.size() == 3);
	v.clear();
	VERIFY(check_invariant(v));
	VERIFY(v.empty());
	VERIFY(v.size() == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));

	{
		hamon::flat_set<int> fs = {3, 1, 4};

		EXPECT_EQ(3u, fs.size());

		fs.clear();

		EXPECT_EQ(0u, fs.size());
	}
}

}	// namespace clear_test

}	// namespace hamon_flat_set_test
