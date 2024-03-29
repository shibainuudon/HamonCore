﻿/**
 *	@file	unit_test_compare_strong_ordering.cpp
 *
 *	@brief	strong_ordering のテスト
 */

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_neq.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/compare/is_lteq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_gteq.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_compare_test
{

namespace strong_ordering_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX17_CONSTEXPR bool test01()
{
	auto x = hamon::strong_ordering::less;
	auto y = hamon::strong_ordering::equivalent;
	auto z = hamon::strong_ordering::greater;
	VERIFY(x == x);
	VERIFY(x != y);
	VERIFY(x != z);

	VERIFY(hamon::strong_ordering::less       == hamon::strong_ordering::less);
	VERIFY(hamon::strong_ordering::less       != hamon::strong_ordering::equal);
	VERIFY(hamon::strong_ordering::less       != hamon::strong_ordering::equivalent);
	VERIFY(hamon::strong_ordering::less       != hamon::strong_ordering::greater);
	VERIFY(hamon::strong_ordering::equivalent == hamon::strong_ordering::equivalent);
	VERIFY(hamon::strong_ordering::equivalent == hamon::strong_ordering::equal);
	VERIFY(hamon::strong_ordering::equivalent != hamon::strong_ordering::greater);
	VERIFY(hamon::strong_ordering::equal      == hamon::strong_ordering::equal);
	VERIFY(hamon::strong_ordering::equal      != hamon::strong_ordering::greater);
	VERIFY(hamon::strong_ordering::greater    == hamon::strong_ordering::greater);

	VERIFY(!(hamon::strong_ordering::less == 0));
	VERIFY( (hamon::strong_ordering::less <  0));
	VERIFY(!(hamon::strong_ordering::less >  0));
	VERIFY( (hamon::strong_ordering::less <= 0));
	VERIFY(!(hamon::strong_ordering::less >= 0));
	VERIFY(!(0 == hamon::strong_ordering::less));
	VERIFY(!(0 <  hamon::strong_ordering::less));
	VERIFY( (0 >  hamon::strong_ordering::less));
	VERIFY(!(0 <= hamon::strong_ordering::less));
	VERIFY( (0 >= hamon::strong_ordering::less));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::strong_ordering::less <=> 0) == hamon::strong_ordering::less);
	VERIFY((0 <=> hamon::strong_ordering::less) == hamon::strong_ordering::greater);
#endif

	VERIFY( (hamon::strong_ordering::equal == 0));
	VERIFY(!(hamon::strong_ordering::equal <  0));
	VERIFY(!(hamon::strong_ordering::equal >  0));
	VERIFY( (hamon::strong_ordering::equal <= 0));
	VERIFY( (hamon::strong_ordering::equal >= 0));
	VERIFY( (0 == hamon::strong_ordering::equal));
	VERIFY(!(0 <  hamon::strong_ordering::equal));
	VERIFY(!(0 >  hamon::strong_ordering::equal));
	VERIFY( (0 <= hamon::strong_ordering::equal));
	VERIFY( (0 >= hamon::strong_ordering::equal));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::strong_ordering::equal <=> 0) == hamon::strong_ordering::equal);
	VERIFY((0 <=> hamon::strong_ordering::equal) == hamon::strong_ordering::equal);
#endif

	VERIFY( (hamon::strong_ordering::equivalent == 0));
	VERIFY(!(hamon::strong_ordering::equivalent <  0));
	VERIFY(!(hamon::strong_ordering::equivalent >  0));
	VERIFY( (hamon::strong_ordering::equivalent <= 0));
	VERIFY( (hamon::strong_ordering::equivalent >= 0));
	VERIFY( (0 == hamon::strong_ordering::equivalent));
	VERIFY(!(0 <  hamon::strong_ordering::equivalent));
	VERIFY(!(0 >  hamon::strong_ordering::equivalent));
	VERIFY( (0 <= hamon::strong_ordering::equivalent));
	VERIFY( (0 >= hamon::strong_ordering::equivalent));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::strong_ordering::equivalent <=> 0) == hamon::strong_ordering::equivalent);
	VERIFY((0 <=> hamon::strong_ordering::equivalent) == hamon::strong_ordering::equivalent);
#endif

	VERIFY(!(hamon::strong_ordering::greater == 0));
	VERIFY(!(hamon::strong_ordering::greater <  0));
	VERIFY( (hamon::strong_ordering::greater >  0));
	VERIFY(!(hamon::strong_ordering::greater <= 0));
	VERIFY( (hamon::strong_ordering::greater >= 0));
	VERIFY(!(0 == hamon::strong_ordering::greater));
	VERIFY( (0 <  hamon::strong_ordering::greater));
	VERIFY(!(0 >  hamon::strong_ordering::greater));
	VERIFY( (0 <= hamon::strong_ordering::greater));
	VERIFY(!(0 >= hamon::strong_ordering::greater));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::strong_ordering::greater <=> 0) == hamon::strong_ordering::greater);
	VERIFY((0 <=> hamon::strong_ordering::greater) == hamon::strong_ordering::less);
#endif

	// Conversions
	VERIFY(hamon::partial_ordering(hamon::strong_ordering::less)       == hamon::partial_ordering::less);
	VERIFY(hamon::partial_ordering(hamon::strong_ordering::equal)      == hamon::partial_ordering::equivalent);
	VERIFY(hamon::partial_ordering(hamon::strong_ordering::equivalent) == hamon::partial_ordering::equivalent);
	VERIFY(hamon::partial_ordering(hamon::strong_ordering::greater)    == hamon::partial_ordering::greater);

	VERIFY(hamon::weak_ordering(hamon::strong_ordering::less)          == hamon::weak_ordering::less);
	VERIFY(hamon::partial_ordering(hamon::strong_ordering::equal)      == hamon::weak_ordering::equivalent);
	VERIFY(hamon::partial_ordering(hamon::strong_ordering::equivalent) == hamon::weak_ordering::equivalent);
	VERIFY(hamon::weak_ordering(hamon::strong_ordering::greater)       == hamon::weak_ordering::greater);

	static_assert(noexcept(hamon::strong_ordering::less == 0), "");
	static_assert(noexcept(hamon::strong_ordering::less != 0), "");
	static_assert(noexcept(hamon::strong_ordering::less <  0), "");
	static_assert(noexcept(hamon::strong_ordering::less >  0), "");
	static_assert(noexcept(hamon::strong_ordering::less <= 0), "");
	static_assert(noexcept(hamon::strong_ordering::less >= 0), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(hamon::strong_ordering::less <=> 0), "");
#endif
	static_assert(noexcept(0 == hamon::strong_ordering::less), "");
	static_assert(noexcept(0 != hamon::strong_ordering::less), "");
	static_assert(noexcept(0 <  hamon::strong_ordering::less), "");
	static_assert(noexcept(0 >  hamon::strong_ordering::less), "");
	static_assert(noexcept(0 <= hamon::strong_ordering::less), "");
	static_assert(noexcept(0 >= hamon::strong_ordering::less), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(0 <=> hamon::strong_ordering::less), "");
#endif

	VERIFY(hamon::is_eq  (hamon::strong_ordering::less)       == false);
	VERIFY(hamon::is_eq  (hamon::strong_ordering::equal)      == true);
	VERIFY(hamon::is_eq  (hamon::strong_ordering::equivalent) == true);
	VERIFY(hamon::is_eq  (hamon::strong_ordering::greater)    == false);
	VERIFY(hamon::is_neq (hamon::strong_ordering::less)       == true);
	VERIFY(hamon::is_neq (hamon::strong_ordering::equal)      == false);
	VERIFY(hamon::is_neq (hamon::strong_ordering::equivalent) == false);
	VERIFY(hamon::is_neq (hamon::strong_ordering::greater)    == true);
	VERIFY(hamon::is_lt  (hamon::strong_ordering::less)       == true);
	VERIFY(hamon::is_lt  (hamon::strong_ordering::equal)      == false);
	VERIFY(hamon::is_lt  (hamon::strong_ordering::equivalent) == false);
	VERIFY(hamon::is_lt  (hamon::strong_ordering::greater)    == false);
	VERIFY(hamon::is_lteq(hamon::strong_ordering::less)       == true);
	VERIFY(hamon::is_lteq(hamon::strong_ordering::equal)      == true);
	VERIFY(hamon::is_lteq(hamon::strong_ordering::equivalent) == true);
	VERIFY(hamon::is_lteq(hamon::strong_ordering::greater)    == false);
	VERIFY(hamon::is_gt  (hamon::strong_ordering::less)       == false);
	VERIFY(hamon::is_gt  (hamon::strong_ordering::equal)      == false);
	VERIFY(hamon::is_gt  (hamon::strong_ordering::equivalent) == false);
	VERIFY(hamon::is_gt  (hamon::strong_ordering::greater)    == true);
	VERIFY(hamon::is_gteq(hamon::strong_ordering::less)       == false);
	VERIFY(hamon::is_gteq(hamon::strong_ordering::equal)      == true);
	VERIFY(hamon::is_gteq(hamon::strong_ordering::equivalent) == true);
	VERIFY(hamon::is_gteq(hamon::strong_ordering::greater)    == true);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, StrongOrderingTest)
{
#if defined(HAMON_COMPARE_USE_INLINE_VARIABLES)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace strong_ordering_test

}	// namespace hamon_compare_test
