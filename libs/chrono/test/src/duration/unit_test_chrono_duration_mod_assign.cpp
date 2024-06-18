/**
 *	@file	unit_test_chrono_duration_mod_assign.cpp
 *
 *	@brief	operator%=() のテスト
 *
 *	constexpr duration& operator%=(const rep& rhs);
 *	constexpr duration& operator%=(const duration& rhs);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_mod_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	Duration d{10};
	static_assert(hamon::is_same<decltype(d %= d), Duration&>::value, "");
	static_assert(hamon::is_same<decltype(d %= 2), Duration&>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(d %= d), "");
	static_assert(noexcept(d %= 2), "");
#endif

	{
		auto& t = (d %= 7);
		VERIFY(&t == &d);
		VERIFY(d.count() == 3);
	}
	{
		auto& t = (d %= Duration{2});
		VERIFY(&t == &d);
		VERIFY(d.count() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, ModAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
}

}	// namespace duration_mod_assign_test

}	// namespace hamon_chrono_test
