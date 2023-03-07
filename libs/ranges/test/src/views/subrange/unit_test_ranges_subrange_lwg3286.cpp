/**
 *	@file	unit_test_ranges_subrange_lwg3286.cpp
 *
 *	@brief	https://cplusplus.github.io/LWG/issue3286
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace lwg3286_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct my_range : public test_input_range<int>
{
	using base_type = test_input_range<int>;
	using base_type::test_range;

	bool called_begin = false;

	HAMON_CXX14_CONSTEXPR auto begin()
	->decltype(base_type::begin())
	{
		called_begin = true;
		return base_type::begin();
	}

	HAMON_CXX14_CONSTEXPR auto end()
	->decltype(base_type::end())
	{
		return base_type::end();
	}

	HAMON_CXX14_CONSTEXPR hamon::size_t size()
	{
		if (called_begin)
		{
			return 0;
		}
		return 3;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int x[] = { 1,2,3 };
	my_range r{x};
	static_assert(!hamon::ranges::forward_range_t<my_range>::value, "");
	static_assert( hamon::ranges::sized_range_t<my_range>::value, "");
	using Subrange = hamon::ranges::subrange<
		hamon::ranges::iterator_t<my_range>,
		hamon::ranges::sentinel_t<my_range>,
		hamon::ranges::subrange_kind::sized
	>;
	Subrange sr = r;
	VERIFY(hamon::ranges::size(sr) == 3);
	
	return true;
}

GTEST_TEST(RangesTest, SubrangeLWG3286Test)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

#undef VERIFY

}	// namespace lwg3286_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
