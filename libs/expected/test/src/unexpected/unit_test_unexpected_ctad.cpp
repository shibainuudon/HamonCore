/**
 *	@file	unit_test_unexpected_ctad.cpp
 *
 *	@brief	コのテスト
 *
 *	template<class E> unexpected(E) -> unexpected<E>;
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Foo{};

HAMON_CXX14_CONSTEXPR bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::unexpected unex{5};
		static_assert(hamon::is_same<decltype(unex), hamon::unexpected<int>>::value, "");
		VERIFY(unex.error() == 5);
	}
	{
		hamon::unexpected unex{Foo{}};
		static_assert(hamon::is_same<decltype(unex), hamon::unexpected<Foo>>::value, "");
	}
	{
		hamon::unexpected unex{hamon::unexpected<int>{10}};
		static_assert(hamon::is_same<decltype(unex), hamon::unexpected<int>>::value, "");
		VERIFY(unex.error() == 10);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, CtadTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctad_test

}	// namespace hamon_unexpected_test
