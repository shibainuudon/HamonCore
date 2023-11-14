/**
 *	@file	unit_test_basic_const_iterator_op_arrow.cpp
 *
 *	@brief	operator-> のテスト
 * 
 *	constexpr const auto* operator->() const
 *	requires is_lvalue_reference_v<iter_reference_t<Iterator>> &&
 *		same_as<remove_cvref_t<iter_reference_t<Iterator>>, value_type>;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace op_arrow_test
{

struct S
{
	int n;

	HAMON_CXX11_CONSTEXPR int func(void) const
	{
		return n;
	}

	HAMON_CXX14_CONSTEXPR int func(void)
	{
		return n * 2;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	S a[] = { S{42} };
	hamon::basic_const_iterator<S*> ci = a;
	VERIFY(42 == ci->func());	// constのほうが呼び出される
	VERIFY(84 == ci.base()->func());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using Iter = random_access_iterator_wrapper<S>;
	S a[] = { S{43} };
	hamon::basic_const_iterator<Iter> ci{Iter{a}};
	VERIFY(43 == ci->func());
//	VERIFY(86 == ci.base()->func());

	static_assert(hamon::is_same<decltype(ci.operator->()), S const*>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, OpArrowTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace op_arrow_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
