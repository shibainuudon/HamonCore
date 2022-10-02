/**
 *	@file	unit_test_compare_partial_ordering.cpp
 *
 *	@brief	partial_ordering のテスト
 */

#include <hamon/compare/partial_ordering.hpp>
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

namespace partial_ordering_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX17_CONSTEXPR bool test01()
{
	VERIFY(hamon::partial_ordering::less == hamon::partial_ordering::less);
	VERIFY(hamon::partial_ordering::less != hamon::partial_ordering::equivalent);
	VERIFY(hamon::partial_ordering::less != hamon::partial_ordering::greater);
	VERIFY(hamon::partial_ordering::less != hamon::partial_ordering::unordered);
	VERIFY(hamon::partial_ordering::equivalent == hamon::partial_ordering::equivalent);
	VERIFY(hamon::partial_ordering::equivalent != hamon::partial_ordering::greater);
	VERIFY(hamon::partial_ordering::equivalent != hamon::partial_ordering::unordered);
	VERIFY(hamon::partial_ordering::greater    == hamon::partial_ordering::greater);
	VERIFY(hamon::partial_ordering::greater    != hamon::partial_ordering::unordered);
	VERIFY(hamon::partial_ordering::unordered  == hamon::partial_ordering::unordered);

	VERIFY(!(hamon::partial_ordering::less == 0));
	VERIFY( (hamon::partial_ordering::less <  0));
	VERIFY(!(hamon::partial_ordering::less >  0));
	VERIFY( (hamon::partial_ordering::less <= 0));
	VERIFY(!(hamon::partial_ordering::less >= 0));
	VERIFY(!(0 == hamon::partial_ordering::less));
	VERIFY(!(0 <  hamon::partial_ordering::less));
	VERIFY( (0 >  hamon::partial_ordering::less));
	VERIFY(!(0 <= hamon::partial_ordering::less));
	VERIFY( (0 >= hamon::partial_ordering::less));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::partial_ordering::less <=> 0) == hamon::partial_ordering::less);
	VERIFY((0 <=> hamon::partial_ordering::less) == hamon::partial_ordering::greater);
#endif

	VERIFY( (hamon::partial_ordering::equivalent == 0));
	VERIFY(!(hamon::partial_ordering::equivalent <  0));
	VERIFY(!(hamon::partial_ordering::equivalent >  0));
	VERIFY( (hamon::partial_ordering::equivalent <= 0));
	VERIFY( (hamon::partial_ordering::equivalent >= 0));
	VERIFY( (0 == hamon::partial_ordering::equivalent));
	VERIFY(!(0 <  hamon::partial_ordering::equivalent));
	VERIFY(!(0 >  hamon::partial_ordering::equivalent));
	VERIFY( (0 <= hamon::partial_ordering::equivalent));
	VERIFY( (0 >= hamon::partial_ordering::equivalent));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::partial_ordering::equivalent <=> 0) == hamon::partial_ordering::equivalent);
	VERIFY((0 <=> hamon::partial_ordering::equivalent) == hamon::partial_ordering::equivalent);
#endif

	VERIFY(!(hamon::partial_ordering::greater == 0));
	VERIFY(!(hamon::partial_ordering::greater <  0));
	VERIFY( (hamon::partial_ordering::greater >  0));
	VERIFY(!(hamon::partial_ordering::greater <= 0));
	VERIFY( (hamon::partial_ordering::greater >= 0));
	VERIFY(!(0 == hamon::partial_ordering::greater));
	VERIFY( (0 <  hamon::partial_ordering::greater));
	VERIFY(!(0 >  hamon::partial_ordering::greater));
	VERIFY( (0 <= hamon::partial_ordering::greater));
	VERIFY(!(0 >= hamon::partial_ordering::greater));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::partial_ordering::greater <=> 0) == hamon::partial_ordering::greater);
	VERIFY((0 <=> hamon::partial_ordering::greater) == hamon::partial_ordering::less);
#endif

	VERIFY(!(hamon::partial_ordering::unordered == 0));
	VERIFY(!(hamon::partial_ordering::unordered <  0));
	VERIFY(!(hamon::partial_ordering::unordered >  0));
	VERIFY(!(hamon::partial_ordering::unordered <= 0));
	VERIFY(!(hamon::partial_ordering::unordered >= 0));
	VERIFY(!(0 == hamon::partial_ordering::unordered));
	VERIFY(!(0 <  hamon::partial_ordering::unordered));
	VERIFY(!(0 >  hamon::partial_ordering::unordered));
	VERIFY(!(0 <= hamon::partial_ordering::unordered));
	VERIFY(!(0 >= hamon::partial_ordering::unordered));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((hamon::partial_ordering::unordered <=> 0) == hamon::partial_ordering::unordered);
	VERIFY((0 <=> hamon::partial_ordering::unordered) == hamon::partial_ordering::unordered);
#endif

	static_assert(noexcept(hamon::partial_ordering::less == 0), "");
	static_assert(noexcept(hamon::partial_ordering::less != 0), "");
	static_assert(noexcept(hamon::partial_ordering::less <  0), "");
	static_assert(noexcept(hamon::partial_ordering::less >  0), "");
	static_assert(noexcept(hamon::partial_ordering::less <= 0), "");
	static_assert(noexcept(hamon::partial_ordering::less >= 0), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(hamon::partial_ordering::less <=> 0), "");
#endif
	static_assert(noexcept(0 == hamon::partial_ordering::less), "");
	static_assert(noexcept(0 != hamon::partial_ordering::less), "");
	static_assert(noexcept(0 <  hamon::partial_ordering::less), "");
	static_assert(noexcept(0 >  hamon::partial_ordering::less), "");
	static_assert(noexcept(0 <= hamon::partial_ordering::less), "");
	static_assert(noexcept(0 >= hamon::partial_ordering::less), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(0 <=> hamon::partial_ordering::less), "");
#endif

	VERIFY(hamon::is_eq  (hamon::partial_ordering::less)       == false);
	VERIFY(hamon::is_eq  (hamon::partial_ordering::equivalent) == true);
	VERIFY(hamon::is_eq  (hamon::partial_ordering::greater)    == false);
	VERIFY(hamon::is_eq  (hamon::partial_ordering::unordered)  == false);
	VERIFY(hamon::is_neq (hamon::partial_ordering::less)       == true);
	VERIFY(hamon::is_neq (hamon::partial_ordering::equivalent) == false);
	VERIFY(hamon::is_neq (hamon::partial_ordering::greater)    == true);
	VERIFY(hamon::is_neq (hamon::partial_ordering::unordered)  == true);
	VERIFY(hamon::is_lt  (hamon::partial_ordering::less)       == true);
	VERIFY(hamon::is_lt  (hamon::partial_ordering::equivalent) == false);
	VERIFY(hamon::is_lt  (hamon::partial_ordering::greater)    == false);
	VERIFY(hamon::is_lt  (hamon::partial_ordering::unordered)  == false);
	VERIFY(hamon::is_lteq(hamon::partial_ordering::less)       == true);
	VERIFY(hamon::is_lteq(hamon::partial_ordering::equivalent) == true);
	VERIFY(hamon::is_lteq(hamon::partial_ordering::greater)    == false);
	VERIFY(hamon::is_lteq(hamon::partial_ordering::unordered)  == false);
	VERIFY(hamon::is_gt  (hamon::partial_ordering::less)       == false);
	VERIFY(hamon::is_gt  (hamon::partial_ordering::equivalent) == false);
	VERIFY(hamon::is_gt  (hamon::partial_ordering::greater)    == true);
	VERIFY(hamon::is_gt  (hamon::partial_ordering::unordered)  == false);
	VERIFY(hamon::is_gteq(hamon::partial_ordering::less)       == false);
	VERIFY(hamon::is_gteq(hamon::partial_ordering::equivalent) == true);
	VERIFY(hamon::is_gteq(hamon::partial_ordering::greater)    == true);
	VERIFY(hamon::is_gteq(hamon::partial_ordering::unordered)  == false);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, PartialOrderingTest)
{
#if defined(HAMON_COMPARE_USE_INLINE_VARIABLES)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace partial_ordering_test

}	// namespace hamon_compare_test
