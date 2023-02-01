/**
 *	@file	unit_test_ranges_subrange_lwg3470.cpp
 *
 *	@brief	https://cplusplus.github.io/LWG/issue3470
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace lwg3470_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	// Visual Studio かつ C++14 だとint*[3]からsubrangeへの変換ができなくてコンパイルエラーになる
#if !(defined(HAMON_MSVC) && (HAMON_CXX_STANDARD < 17))
	// GCC9 だとint*[3]からsubrangeへの変換ができなくてコンパイルエラーになる
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000))
	// The example from LWG3470, using implicit conversion.
	int a[3] = { 1, 2, 3 };
	int* b[3] = { &a[2], &a[0], &a[1] };
	hamon::ranges::subrange<const int* const*> c = b;
	VERIFY(c.begin() == b + 0);
	VERIFY(c.end() == b + 3);

	// Also test CTAD and a subrange-to-subrange conversion.
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	auto d = hamon::ranges::subrange(b);
	static_assert(hamon::same_as_t<hamon::ranges::subrange<int**>, decltype(d)>::value, "");
#else
	hamon::ranges::subrange<int**> d = b;
#endif
	VERIFY(d.begin() == b + 0);
	VERIFY(d.end() == b + 3);

	hamon::ranges::subrange<const int* const*> e = d;
	VERIFY(e.begin() == b + 0);
	VERIFY(e.end() == b + 3);
#endif
#endif

	return true;
}

GTEST_TEST(RangesTest, SubrangeLWG3470Test)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

#undef VERIFY

}	// namespace lwg3470_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
