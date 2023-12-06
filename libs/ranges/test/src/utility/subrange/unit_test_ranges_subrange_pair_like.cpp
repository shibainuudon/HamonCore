/**
 *	@file	unit_test_ranges_subrange_pair_like.cpp
 *
 *	@brief	ranges::subrange をPair-Like型に変換するテスト
 */

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <utility>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace pair_like_test
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
		ForwardRange r{x};
		ForwardUnsizedSubrange sr(r.begin(), r.end());
		std::pair<ForwardIter, ForwardSent> p = sr;
		VERIFY(p.first.m_ptr == x);
		VERIFY(p.second.m_it.m_ptr == x+5);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int x[] = {1, 2, 3, 4, 5};
		ForwardRange r{x};
		ForwardUnsizedSubrange sr(r.begin(), r.end());
		std::tuple<ForwardIter, ForwardSent> t = sr;
		VERIFY(hamon::adl_get<0>(t).m_ptr == x);
		VERIFY(hamon::adl_get<1>(t).m_it.m_ptr == x+5);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangePairLikeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

#undef VERIFY

}	// namespace pair_like_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
