/**
 *	@file	unit_test_ranges_single_view.cpp
 *
 *	@brief	ranges::single_view のテスト
 */

#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{
namespace single_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int n = 4;
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::single_view s{n};
#else
	hamon::ranges::single_view<int> s{n};
#endif
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(s)>, int>::value, "");
	VERIFY(hamon::ranges::size(s) == 1);

	VERIFY(s.empty() == false);
	VERIFY(s.size() == 1);

	int count = 0;
	for (auto i : s)
	{
		VERIFY(i == 4);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*hamon::ranges::begin(s) == 4);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::ranges::single_view<long> const s {};
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(s)>, long>::value, "");
	VERIFY(hamon::ranges::size(s) == 1);

	VERIFY(s.empty() == false);
	VERIFY(s.size() == 1);

	int count = 0;
	for (auto l : s)
	{
		VERIFY(l == 0L);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*hamon::ranges::begin(s) == 0L);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	hamon::ranges::single_view<float> s(hamon::in_place, 0.5f);
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(s)>, float>::value, "");
	VERIFY(hamon::ranges::size(s) == 1);

	VERIFY(s.empty() == false);
	VERIFY(s.size() == 1);

	int count = 0;
	for (auto l : s)
	{
		VERIFY(l == 0.5f);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*hamon::ranges::begin(s) == 0.5f);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	auto s = hamon::views::single('a');
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(s)>, char>::value, "");
	VERIFY(hamon::ranges::size(s) == 1);
	VERIFY(*hamon::ranges::begin(s) == 'a');

	VERIFY(s.empty() == false);
	VERIFY(s.size() == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SingleViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace single_view_test
}	// namespace hamon_ranges_test
