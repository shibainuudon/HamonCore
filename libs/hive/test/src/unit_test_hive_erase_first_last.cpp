/**
 *	@file	unit_test_hive_erase_first_last.cpp
 *
 *	@brief	erase のテスト
 *
 *	iterator erase(const_iterator first, const_iterator last);
 */

#include <hamon/hive.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace erase_first_last_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using iterator       = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().erase(hamon::declval<const_iterator>(), hamon::declval<const_iterator>())), iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().erase(hamon::declval<const_iterator>(), hamon::declval<const_iterator>())), "");

	{
		Hive v{1,2,3,4,5};
		auto r = v.erase(v.begin(), hamon::next(v.begin(), 4));
		VERIFY(r != v.end());
		VERIFY(v.size() == 1u);
	}
	{
		Hive v{1,2,3,4,5};
		auto r = v.erase(hamon::next(v.begin(), 2), hamon::next(v.begin(), 5));
		VERIFY(r == v.end());
		VERIFY(v.size() == 2u);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, EraseFirstLastTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace erase_first_last_test

}	// namespace hamon_hive_test
