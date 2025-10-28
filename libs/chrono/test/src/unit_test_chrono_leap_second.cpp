/**
 *	@file	unit_test_chrono_leap_second.cpp
 *
 *	@brief	leap_second のテスト
 */

#include <hamon/chrono/leap_second.hpp>
#include <hamon/compare.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace leap_second_test
{

static_assert( hamon::is_copy_constructible<hamon::chrono::leap_second>::value, "");
static_assert( hamon::is_copy_assignable<hamon::chrono::leap_second>::value, "");
static_assert( hamon::is_move_constructible<hamon::chrono::leap_second>::value, "");
static_assert( hamon::is_move_assignable<hamon::chrono::leap_second>::value, "");

inline HAMON_CXX11_CONSTEXPR hamon::chrono::leap_second
test_leap_second_create(const hamon::chrono::sys_seconds& date, const hamon::chrono::seconds& value)
{
	return hamon::chrono::leap_second{ hamon::chrono::detail::private_ctor_tag{}, date, value };
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool copy_ctor_test()
{
	auto a = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{0}}, hamon::chrono::seconds{1});

	{
		hamon::chrono::leap_second b = a;

		//  operator== only compares the date member.
		VERIFY(a.date() == b.date());
		VERIFY(a.value() == b.value());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool copy_assign_test()
{
	auto a = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{0}}, hamon::chrono::seconds{1});
	auto b = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{10}}, hamon::chrono::seconds{15});

	//  operator== only compares the date member.
	VERIFY(a.date() != b.date());
	VERIFY(a.value() != b.value());

	{
		auto& result = (b = a);
		static_assert(hamon::is_same<decltype(result), hamon::chrono::leap_second&>::value, "");
		VERIFY(hamon::addressof(result) == hamon::addressof(b));

		VERIFY(a.date() == b.date());
		VERIFY(a.value() == b.value());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool date_test()
{
	auto a = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{0}}, hamon::chrono::seconds{1});

	static_assert(hamon::is_same<decltype(a.date()), hamon::chrono::sys_seconds>::value, "");
	static_assert(noexcept(a.date()), "");

	VERIFY(a.date() == hamon::chrono::sys_seconds{hamon::chrono::seconds{0}});

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool value_test()
{
	auto a = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{0}}, hamon::chrono::seconds{1});

	static_assert(hamon::is_same<decltype(a.value()), hamon::chrono::seconds>::value, "");
	static_assert(noexcept(a.value()), "");

	VERIFY(a.value() == hamon::chrono::seconds{1});

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool comparison_test()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() == hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() != hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() <  hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() >  hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() <= hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() >= hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() == hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() != hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() <  hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() >  hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() <= hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() >= hamon::declval<hamon::chrono::leap_second>()), "");

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() == hamon::declval<hamon::chrono::sys_seconds>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() != hamon::declval<hamon::chrono::sys_seconds>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() <  hamon::declval<hamon::chrono::sys_seconds>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() >  hamon::declval<hamon::chrono::sys_seconds>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() <= hamon::declval<hamon::chrono::sys_seconds>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() >= hamon::declval<hamon::chrono::sys_seconds>()), bool>::value, "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() == hamon::declval<hamon::chrono::sys_seconds>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() != hamon::declval<hamon::chrono::sys_seconds>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() <  hamon::declval<hamon::chrono::sys_seconds>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() >  hamon::declval<hamon::chrono::sys_seconds>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() <= hamon::declval<hamon::chrono::sys_seconds>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() >= hamon::declval<hamon::chrono::sys_seconds>()), "");

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() == hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() != hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() <  hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() >  hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() <= hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() >= hamon::declval<hamon::chrono::leap_second>()), bool>::value, "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() == hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() != hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() <  hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() >  hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() <= hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() >= hamon::declval<hamon::chrono::leap_second>()), "");

	auto a = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{0}}, hamon::chrono::seconds{0});
	auto b = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{0}}, hamon::chrono::seconds{1});
	auto c = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{1}}, hamon::chrono::seconds{0});
	auto d = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{1}}, hamon::chrono::seconds{1});
	auto e = test_leap_second_create(hamon::chrono::sys_seconds{hamon::chrono::seconds{2}}, hamon::chrono::seconds{0});

	VERIFY(!(c == a));
	VERIFY(!(c == b));
	VERIFY( (c == c));
	VERIFY( (c == d));
	VERIFY(!(c == e));

	VERIFY( (c != a));
	VERIFY( (c != b));
	VERIFY(!(c != c));
	VERIFY(!(c != d));
	VERIFY( (c != e));

	VERIFY(!(c <  a));
	VERIFY(!(c <  b));
	VERIFY(!(c <  c));
	VERIFY(!(c <  d));
	VERIFY( (c <  e));

	VERIFY( (c >  a));
	VERIFY( (c >  b));
	VERIFY(!(c >  c));
	VERIFY(!(c >  d));
	VERIFY(!(c >  e));

	VERIFY(!(c <= a));
	VERIFY(!(c <= b));
	VERIFY( (c <= c));
	VERIFY( (c <= d));
	VERIFY( (c <= e));

	VERIFY( (c >= a));
	VERIFY( (c >= b));
	VERIFY( (c >= c));
	VERIFY( (c >= d));
	VERIFY(!(c >= e));

	VERIFY(!(c == a.date()));
	VERIFY(!(c == b.date()));
	VERIFY( (c == c.date()));
	VERIFY( (c == d.date()));
	VERIFY(!(c == e.date()));

	VERIFY( (c != a.date()));
	VERIFY( (c != b.date()));
	VERIFY(!(c != c.date()));
	VERIFY(!(c != d.date()));
	VERIFY( (c != e.date()));

	VERIFY(!(c <  a.date()));
	VERIFY(!(c <  b.date()));
	VERIFY(!(c <  c.date()));
	VERIFY(!(c <  d.date()));
	VERIFY( (c <  e.date()));

	VERIFY( (c >  a.date()));
	VERIFY( (c >  b.date()));
	VERIFY(!(c >  c.date()));
	VERIFY(!(c >  d.date()));
	VERIFY(!(c >  e.date()));

	VERIFY(!(c <= a.date()));
	VERIFY(!(c <= b.date()));
	VERIFY( (c <= c.date()));
	VERIFY( (c <= d.date()));
	VERIFY( (c <= e.date()));

	VERIFY( (c >= a.date()));
	VERIFY( (c >= b.date()));
	VERIFY( (c >= c.date()));
	VERIFY( (c >= d.date()));
	VERIFY(!(c >= e.date()));

	VERIFY(!(c.date() == a));
	VERIFY(!(c.date() == b));
	VERIFY( (c.date() == c));
	VERIFY( (c.date() == d));
	VERIFY(!(c.date() == e));

	VERIFY( (c.date() != a));
	VERIFY( (c.date() != b));
	VERIFY(!(c.date() != c));
	VERIFY(!(c.date() != d));
	VERIFY( (c.date() != e));

	VERIFY(!(c.date() <  a));
	VERIFY(!(c.date() <  b));
	VERIFY(!(c.date() <  c));
	VERIFY(!(c.date() <  d));
	VERIFY( (c.date() <  e));

	VERIFY( (c.date() >  a));
	VERIFY( (c.date() >  b));
	VERIFY(!(c.date() >  c));
	VERIFY(!(c.date() >  d));
	VERIFY(!(c.date() >  e));

	VERIFY(!(c.date() <= a));
	VERIFY(!(c.date() <= b));
	VERIFY( (c.date() <= c));
	VERIFY( (c.date() <= d));
	VERIFY( (c.date() <= e));

	VERIFY( (c.date() >= a));
	VERIFY( (c.date() >= b));
	VERIFY( (c.date() >= c));
	VERIFY( (c.date() >= d));
	VERIFY(!(c.date() >= e));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() <=> hamon::declval<hamon::chrono::leap_second>()), hamon::strong_ordering>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::leap_second>() <=> hamon::declval<hamon::chrono::sys_seconds>()), hamon::strong_ordering>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::chrono::sys_seconds>() <=> hamon::declval<hamon::chrono::leap_second>()), hamon::strong_ordering>::value, "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() <=> hamon::declval<hamon::chrono::leap_second>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::leap_second>() <=> hamon::declval<hamon::chrono::sys_seconds>()), "");
	static_assert(noexcept(hamon::declval<hamon::chrono::sys_seconds>() <=> hamon::declval<hamon::chrono::leap_second>()), "");

	VERIFY(hamon::is_gt(c <=> a));
	VERIFY(hamon::is_gt(c <=> b));
	VERIFY(hamon::is_eq(c <=> c));
	VERIFY(hamon::is_eq(c <=> d));
	VERIFY(hamon::is_lt(c <=> e));

	VERIFY(hamon::is_gt(c <=> a.date()));
	VERIFY(hamon::is_gt(c <=> b.date()));
	VERIFY(hamon::is_eq(c <=> c.date()));
	VERIFY(hamon::is_eq(c <=> d.date()));
	VERIFY(hamon::is_lt(c <=> e.date()));

	VERIFY(hamon::is_gt(c.date() <=> a));
	VERIFY(hamon::is_gt(c.date() <=> b));
	VERIFY(hamon::is_eq(c.date() <=> c));
	VERIFY(hamon::is_eq(c.date() <=> d));
	VERIFY(hamon::is_lt(c.date() <=> e));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(ChronoTest, LeapSecondTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(copy_ctor_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(copy_assign_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(date_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(value_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(comparison_test());
}

}	// namespace leap_second_test

}	// namespace hamon_chrono_test
