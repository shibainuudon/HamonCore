/**
 *	@file	unit_test_ranges_subrange_advance.cpp
 *
 *	@brief	ranges::subrange::advance のテスト
 */

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/subrange_kind.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace advance_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int x[] = {1, 2, 3, 4, 5};
	hamon::ranges::subrange<int*> sr(x, x+5);
	VERIFY(sr.begin() == x);
	VERIFY(sr.size() == 5);
	sr.advance(1);
	VERIFY(sr.begin() == x+1);
	VERIFY(sr.size() == 4);
	sr.advance(3);
	VERIFY(sr.begin() == x+4);
	VERIFY(sr.size() == 1);
	sr.advance(-2);
	VERIFY(sr.begin() == x+2);
	VERIFY(sr.size() == 3);
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	using Iter = bidirectional_iterator_wrapper<int>;
	int x[] = {1, 2, 3, 4, 5};
	hamon::ranges::subrange<Iter> sr(Iter{x}, Iter{x+5});
	VERIFY(sr.begin().m_ptr == x);
//	VERIFY(sr.size() == 5);
	sr.advance(1);
	VERIFY(sr.begin().m_ptr == x+1);
//	VERIFY(sr.size() == 4);
	sr.advance(3);
	VERIFY(sr.begin().m_ptr == x+4);
//	VERIFY(sr.size() == 1);
	sr.advance(-2);
	VERIFY(sr.begin().m_ptr == x+2);
//	VERIFY(sr.size() == 3);
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	using Iter = bidirectional_iterator_wrapper<int>;
	int x[] = {1, 2, 3, 4, 5};
	hamon::ranges::subrange<Iter, Iter, hamon::ranges::subrange_kind::sized> sr(Iter{x}, Iter{x+5}, 5);
	VERIFY(sr.begin().m_ptr == x);
	VERIFY(sr.size() == 5);
	sr.advance(1);
	VERIFY(sr.begin().m_ptr == x+1);
	VERIFY(sr.size() == 4);
	sr.advance(3);
	VERIFY(sr.begin().m_ptr == x+4);
	VERIFY(sr.size() == 1);
	sr.advance(-2);
	VERIFY(sr.begin().m_ptr == x+2);
	VERIFY(sr.size() == 3);
	return true;
}

GTEST_TEST(RangesTest, SubrangeAdvanceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace advance_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
