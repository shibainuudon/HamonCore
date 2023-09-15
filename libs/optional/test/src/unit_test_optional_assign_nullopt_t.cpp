/**
 *	@file	unit_test_optional_assign_nullopt_t.cpp
 *
 *	@brief	nullopt_tからの代入演算子のテスト
 *
 *	constexpr optional<T>& operator=(nullopt_t) noexcept;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace assign_nullopt_t_test
{

static bool s_dtor_invoked = false;

struct S
{
	~S()
	{
		s_dtor_invoked = true;
	}
};

static_assert( hamon::is_nothrow_assignable<hamon::optional<int>&, hamon::nullopt_t>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::optional<hamon::string>&, hamon::nullopt_t>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::optional<S>&, hamon::nullopt_t>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::optional<int> o;
		VERIFY(!o.has_value());
		o = hamon::nullopt;
		VERIFY(!o.has_value());
	}
	{
		hamon::optional<int> o{42};
		VERIFY(o.has_value());
		o = hamon::nullopt;
		VERIFY(!o.has_value());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(OptionalTest, AssignNulloptTTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));

	{
		s_dtor_invoked = false;
		hamon::optional<S> o{hamon::in_place};
		EXPECT_TRUE(o.has_value());
		EXPECT_FALSE(s_dtor_invoked);
		o = hamon::nullopt;
		EXPECT_FALSE(o.has_value());
		EXPECT_TRUE(s_dtor_invoked);
	}
}

}	// namespace assign_nullopt_t_test

}	// namespace hamon_optional_test
