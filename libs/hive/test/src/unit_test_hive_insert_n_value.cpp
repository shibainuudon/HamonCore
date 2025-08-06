/**
 *	@file	unit_test_hive_insert_n_value.cpp
 *
 *	@brief	insert のテスト
 *
 *	void insert(size_type n, const T& x);
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

namespace insert_n_value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().insert(hamon::declval<SizeType>(), hamon::declval<T const&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().insert(hamon::declval<SizeType>(), hamon::declval<T const&>())), "");

	Hive v;
	VERIFY(v.empty());
	VERIFY(v.size() == 0u);
	{
		SizeType const n{50};
		T const x{42};
		v.insert(n, x);
		VERIFY(*v.begin() == T{42});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == x * static_cast<T>(n));
	}
	VERIFY(v.size() == 50u);
	{
		SizeType const n{100};
		T const x{13};
		v.insert(n, x);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{50*42 + 100*13});
	}
	VERIFY(v.size() == 150u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, InsertNValueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace insert_n_value_test

}	// namespace hamon_hive_test
