/**
 *	@file	unit_test_hive_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	void clear() noexcept;
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

namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().clear()), void>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().clear()), "");

	Hive v;
	VERIFY(v.empty());

	v.clear();
	VERIFY(v.empty());

	v.insert(SizeType{100}, T{3});
	VERIFY(!v.empty());
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{300});

	v.clear();
	VERIFY(v.empty());
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});

	v.insert(SizeType{10}, T{3});
	VERIFY(!v.empty());
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{30});

	v.clear();
	VERIFY(v.empty());
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace clear_test

}	// namespace hamon_hive_test
