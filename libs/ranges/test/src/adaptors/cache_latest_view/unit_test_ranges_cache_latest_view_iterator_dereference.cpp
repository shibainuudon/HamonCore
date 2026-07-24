/**
 *	@file	unit_test_ranges_cache_latest_view_iterator_dereference.cpp
 *
 *	@brief	operator*() のテスト
 *
 *	constexpr range_reference_t<V>& operator*() const;
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using I = decltype(hamon::declval<CLV&>().begin());

	static_assert(has_dereference<I&>::value, "");
	static_assert(has_dereference<I const&>::value, "");

	static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int&>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int&>::value, "");

	int a[] = {2,3,4,5};
	V v(a);

	CLV clv(v);

	auto it = clv.begin();
	VERIFY(*it == 2);
	VERIFY(*it == 2);
	++it;
	VERIFY(*it == 3);
	VERIFY(*it == 3);

	return true;
}

struct square
{
	template <typename T>
	constexpr auto operator()(T n) const
	{
		return n * n;
	}
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<long>;
	using TV = hamon::ranges::transform_view<V, square>;
	using CLV = hamon::ranges::cache_latest_view<TV>;
	using I = decltype(hamon::declval<CLV&>().begin());

	static_assert(has_dereference<I&>::value, "");
	static_assert(has_dereference<I const&>::value, "");

	static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), long&>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), long&>::value, "");

	long a[] = {2,3,4,5};
	V v(a);
	TV tv(v, square{});
	CLV clv(tv);

	auto it = clv.begin();
	VERIFY(*it == 4);
	VERIFY(*it == 4);
	++it;
	VERIFY(*it == 9);
	VERIFY(*it == 9);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_dereference_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
