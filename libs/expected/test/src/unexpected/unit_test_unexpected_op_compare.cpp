/**
 *	@file	unit_test_unexpected_op_compare.cpp
 *
 *	@brief	operator==() のテスト
 *
 *	template<class E2>
 *	friend constexpr bool operator==(const unexpected&, const unexpected<E2>&);
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::unexpected<E> const unex1{E{2}};
	hamon::unexpected<E> const unex2{E{3}};
	hamon::unexpected<E> const unex3{E{2}};

	static_assert(hamon::is_same<decltype(unex1 == unex1), bool>::value, "");
	static_assert(hamon::is_same<decltype(unex1 != unex1), bool>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert(noexcept(unex1 == unex1), "");
	static_assert(noexcept(unex1 != unex1), "");
#endif

	VERIFY( (unex1 == unex1));
	VERIFY(!(unex1 == unex2));
	VERIFY( (unex1 == unex3));

	VERIFY(!(unex1 != unex1));
	VERIFY( (unex1 != unex2));
	VERIFY(!(unex1 != unex3));

	return true;
}

struct Error
{
	int i;
	friend constexpr bool operator==(const Error& lhs, const Error& rhs) { return lhs.i == rhs.i; }
	friend constexpr bool operator==(const Error& lhs, int rhs) { return lhs.i == rhs; }
};

HAMON_CXX14_CONSTEXPR bool test2()
{
	hamon::unexpected<Error> const unex1{Error{4}};
	hamon::unexpected<Error> const unex2{Error{5}};
	hamon::unexpected<int>   const unex3{4};
	hamon::unexpected<int>   const unex4{5};

	static_assert(hamon::is_same<decltype(unex1 == unex4), bool>::value, "");
	static_assert(hamon::is_same<decltype(unex1 != unex4), bool>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert(!noexcept(unex1 == unex4), "");
	static_assert(!noexcept(unex1 != unex4), "");
#endif

	VERIFY( (unex1 == unex1));
	VERIFY(!(unex1 == unex2));
	VERIFY( (unex1 == unex3));
	VERIFY(!(unex1 == unex4));

	VERIFY(!(unex1 != unex1));
	VERIFY( (unex1 != unex2));
	VERIFY(!(unex1 != unex3));
	VERIFY( (unex1 != unex4));

	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, OpCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace op_compare_test

}	// namespace hamon_unexpected_test
