/**
 *	@file	unit_test_optional_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	constexpr ~optional();
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace dtor_test
{

struct Trivial {};

static bool s_dtor_invoked = false;

struct NonTrivial
{
	~NonTrivial()
	{
		s_dtor_invoked = true;
	}
};

static_assert( hamon::is_trivially_destructible<Trivial>::value, "");
static_assert(!hamon::is_trivially_destructible<NonTrivial>::value, "");

static_assert( hamon::is_trivially_destructible<hamon::optional<Trivial>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::optional<NonTrivial>>::value, "");

GTEST_TEST(OptionalTest, DtorTest)
{
	s_dtor_invoked = false;
	{
		hamon::optional<NonTrivial> t{hamon::in_place};
		EXPECT_FALSE(s_dtor_invoked);
	}
	EXPECT_TRUE(s_dtor_invoked);
}

}	// namespace dtor_test

}	// namespace hamon_optional_test
