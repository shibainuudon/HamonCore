/**
 *	@file	unit_test_ranges_chunk_view_ctor_base_n.cpp
 *
 *	@brief	baseとnを引数に取るコンスタラクタのテスト
 *
 *	constexpr explicit chunk_view(V base, range_difference_t<V> n);
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace ctor_base_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = View<T>;
	using D = hamon::ranges::range_difference_t<V>;
	using CV = hamon::ranges::chunk_view<V>;

	static_assert( hamon::is_constructible<CV, V, D>::value, "");
	static_assert(!hamon::is_constructible<CV, V>::value, "");
	static_assert(!hamon::is_constructible<CV, D>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, V, D>::value, "");

	T a[] = {1,2,3};
	V v(a);
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::chunk_view cv{v, 2};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{v, 2};
#endif
	VERIFY(cv.begin() != cv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using CV = hamon::ranges::chunk_view<hamon::views::all_t<int(&)[4]>>;

	int a[] = {1,2,3,4};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::chunk_view cv{a, 2};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{a, 2};
#endif

	VERIFY(cv.begin() != cv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewCtorBaseNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<int, test_input_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<long, test_forward_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<short, test_bidirectional_view>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test00<char, test_random_access_view>()));
}

}	// namespace ctor_base_n_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
