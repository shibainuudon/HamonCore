/**
 *	@file	unit_test_hive_insert_copy.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(const T& x);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace insert_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using iterator = typename Hive::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().insert(hamon::declval<T const&>())), iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().insert(hamon::declval<T const&>())), "");

	Hive v;
	VERIFY(v.empty());
	VERIFY(v.size() == 0u);
	{
		T const t{10};
		auto ret = v.insert(t);
		VERIFY(ret == v.begin());
		VERIFY(hamon::accumulate(v.rbegin(), v.rend(), T{}, hamon::plus<T>{}) == T{10});
	}
	VERIFY(v.size() == 1u);
	{
		T const t{20};
		auto ret = v.insert(t);
		VERIFY(*ret == T{20});
		VERIFY(hamon::accumulate(v.rbegin(), v.rend(), T{}, hamon::plus<T>{}) == T{30});
	}
	VERIFY(v.size() == 2u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, InsertCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace insert_copy_test

}	// namespace hamon_hive_test
