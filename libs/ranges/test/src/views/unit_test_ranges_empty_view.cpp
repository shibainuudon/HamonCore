/**
 *	@file	unit_test_ranges_empty_view.cpp
 *
 *	@brief	ranges::empty_view のテスト
 */

#include <hamon/ranges/views/empty_view.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{
namespace empty_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::ranges::view_t<hamon::ranges::empty_view<T>>::value, "");
	static_assert(hamon::ranges::borrowed_range_t<hamon::ranges::empty_view<T>>::value, "");

	hamon::ranges::empty_view<T> e{};

	VERIFY(e.begin() == nullptr);
	VERIFY(e.end()   == nullptr);
	VERIFY(e.data()  == nullptr);
	VERIFY(e.size()  == 0);
	VERIFY(e.empty());

	VERIFY(hamon::ranges::begin(e) == nullptr);
	VERIFY(hamon::ranges::end(e)   == nullptr);
	VERIFY(hamon::ranges::data(e)  == nullptr);
	VERIFY(hamon::ranges::size(e)  == 0);
	VERIFY(hamon::ranges::empty(e));

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	auto e2 = hamon::ranges::views::empty<T>;
	static_assert(hamon::is_same<decltype(e2), hamon::ranges::empty_view<T>>::value, "");
#endif

	return true;
}

#undef VERIFY

struct A {};

GTEST_TEST(RangesTest, EmptyViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());
}

}	// namespace empty_view_test
}	// namespace hamon_ranges_test
