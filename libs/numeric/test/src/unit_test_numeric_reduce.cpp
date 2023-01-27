/**
 *	@file	unit_test_numeric_reduce.cpp
 *
 *	@brief	reduce のテスト
 */

#include <hamon/numeric/reduce.hpp>
#include <hamon/functional/multiplies.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// conversion from '...' to '...', possible loss of data

namespace hamon_numeric_test
{

namespace reduce_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[5] = {1, 2, 3, 4, 5};
	test_container<int, input_iterator_wrapper> con(a);
	int res = hamon::reduce(con.begin(), con.end());
	VERIFY(res == 15);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	bool b[] = {true, false, true, true, false, true, false, true, true, false};
	int res = hamon::reduce(hamon::begin(b), hamon::end(b), 100);
	VERIFY(res == 106);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	auto res = hamon::reduce(hamon::begin(a), hamon::end(a), (short)11);
	static_assert(std::is_same<decltype(res), short>::value, "");
	VERIFY(res == 66);

	auto res2 = hamon::reduce(hamon::begin(a), hamon::end(a), -1l, hamon::multiplies<>{});
	static_assert(std::is_same<decltype(res2), long>::value, "");
	VERIFY(res2 == -3628800);

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, ReduceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace reduce_test

}	// namespace hamon_numeric_test

HAMON_WARNING_POP()
