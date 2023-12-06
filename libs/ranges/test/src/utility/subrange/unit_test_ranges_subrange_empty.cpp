/**
 *	@file	unit_test_ranges_subrange_empty.cpp
 *
 *	@brief	ranges::subrange::emptyのテスト
 */

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using ForwardRange = test_forward_range<int>;

using ForwardIter = hamon::ranges::iterator_t<ForwardRange>;
using ForwardSent = hamon::ranges::sentinel_t<ForwardRange>;

using ForwardUnsizedSubrange =
	hamon::ranges::subrange<
		hamon::ranges::iterator_t<ForwardRange>,
		hamon::ranges::sentinel_t<ForwardRange>,
		hamon::ranges::subrange_kind::unsized
	>;

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x, x};
		ForwardUnsizedSubrange sr(r.begin(), r.end());
		VERIFY(sr.empty());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardUnsizedSubrange sr(r.begin(), r.end());
		VERIFY(!sr.empty());
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		ForwardUnsizedSubrange sr(ForwardIter{nullptr}, ForwardSent{nullptr});
		VERIFY(sr.empty());
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeEmptyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace empty_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
