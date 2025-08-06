/**
 *	@file	unit_test_hive_ctor_range.cpp
 *
 *	@brief	range を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R>
 *	hive(from_range_t, R&& rg, const Allocator& = Allocator());
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_hive_test
{

namespace ctor_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;
	using Range = RangeWrapper<T>;

	static_assert( hamon::is_constructible           <Hive, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, hamon::from_range_t, Range>::value, "");

	static_assert( hamon::is_constructible           <Hive, hamon::from_range_t, Range, const Allocator&>::value, "");
	static_assert(!hamon::is_nothrow_constructible   <Hive, hamon::from_range_t, Range, const Allocator&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Hive, hamon::from_range_t, Range, const Allocator&>::value, "");
	static_assert(!hamon::is_trivially_constructible <Hive, hamon::from_range_t, Range, const Allocator&>::value, "");

	Allocator alloc;
	T a[] = {T{1}, T{2}, T{3}};
	Range r(a);

	{
		Hive v(hamon::from_range, r);
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		Hive v(hamon::from_range, r, alloc);
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.rbegin(), v.rend(), T{}, hamon::plus<T>{}) == T{6});
	}

	return true;
}

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return
		test_impl<T, test_input_range>() &&
		test_impl<T, test_forward_range>() &&
		test_impl<T, test_bidirectional_range>() &&
		test_impl<T, test_random_access_range>() &&
		test_impl<T, test_contiguous_range>() &&
		test_impl<T, test_input_sized_range>() &&
		test_impl<T, test_forward_sized_range>() &&
		test_impl<T, test_bidirectional_sized_range>() &&
		test_impl<T, test_random_access_sized_range>() &&
		test_impl<T, test_contiguous_sized_range>();
}

#undef VERIFY

GTEST_TEST(HiveTest, CtorRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace ctor_range_test

}	// namespace hamon_hive_test
