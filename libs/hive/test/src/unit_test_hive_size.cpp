/**
 *	@file	unit_test_hive_size.cpp
 *
 *	@brief	size のテスト
 *
 *	size_type size() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().size()), "");

	Hive v;
	VERIFY(v.size() == 0u);

	v.emplace(T{1});
	VERIFY(v.size() == 1u);

	v.emplace(T{1});
	VERIFY(v.size() == 2u);

	v.clear();
	VERIFY(v.size() == 0u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, SizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace size_test

}	// namespace hamon_hive_test
