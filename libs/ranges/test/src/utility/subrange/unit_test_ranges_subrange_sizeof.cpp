/**
 *	@file	unit_test_ranges_subrange_sizeof.cpp
 *
 *	@brief	ranges::subrange::sizeof のテスト
 */

#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace sizeof_test
{

GTEST_TEST(RangesTest, SubrangeSizeofTest)
{
	// contiguous_iterator sized
	{
		using Iter = contiguous_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::sized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent), "");
	}
	// random_access_iterator sized
	{
		using Iter = random_access_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::sized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent), "");
	}
	// bidirectional_iterator sized
	{
		using Iter = bidirectional_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::sized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent) + sizeof(hamon::iter_difference_t<Iter>), "");
	}
	// bidirectional_iterator unsized
	{
		using Iter = bidirectional_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::unsized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent), "");
	}
	// forward_iterator sized
	{
		using Iter = forward_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::sized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent) + sizeof(hamon::iter_difference_t<Iter>), "");
	}
	// forward_iterator unsized
	{
		using Iter = forward_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::unsized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent), "");
	}
	// input_iterator sized
	{
		using Iter = input_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::sized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent) + sizeof(hamon::iter_difference_t<Iter>), "");
	}
	// input_iterator unsized
	{
		using Iter = input_iterator_wrapper<int>;
		using Sent = test_sentinel<Iter>;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::unsized>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent), "");
	}
	// int*, int*
	{
		using Iter = int*;
		using Sent = int*;
		using Subrange = hamon::ranges::subrange<Iter, Sent>;
		static_assert(sizeof(Subrange) == sizeof(Iter) + sizeof(Sent), "");
	}

	// sentinelが空オブジェクトのときは、サイズが最適化される可能性がある
#if defined(HAMON_HAS_CXX20_NO_UNIQUE_ADDRESS)
#if !(defined(HAMON_MSVC) && (HAMON_MSVC <= 1938))
	// int*, hamon::unreachable_sentinel_t
	{
		using Iter = int*;
		using Sent = hamon::unreachable_sentinel_t;
		using Subrange = hamon::ranges::subrange<Iter, Sent,
			hamon::ranges::subrange_kind::unsized>;
		static_assert(sizeof(Subrange) == sizeof(Iter), "");
	}
#endif
#endif
}

}	// namespace sizeof_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
