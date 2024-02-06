/**
 *	@file	unit_test_ranges_common_view_adaptor.cpp
 *
 *	@brief	views::common のテスト
 *
 *	hamon::views::common
 */

#include <hamon/ranges/adaptors/common_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace common_view_test
{
namespace adaptor_test
{

template <
	typename InputIterator1,
	typename InputIterator2
>
HAMON_CXX14_CONSTEXPR bool
legacy_equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2)
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(*first1 == *first2))
		{
			return false;
		}
	}

	return true;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	int a[] = {1,2,3};
	V v(a);

	using CV = hamon::ranges::common_view<V>;

	// views::common(v)
	{
		auto cv = hamon::views::common(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), a));
	}
	// v | views::common
	{
		auto cv = v | hamon::views::common;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_common_view<int>;
	int a[] = {1,2,3};
	V v(a);

	using CV = V;

	// views::common(v)
	{
		auto cv = hamon::views::common(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), v.begin()));
	}
	// v | views::common
	{
		auto cv = v | hamon::views::common;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), v.begin()));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V = test_forward_range<int>;
	int a[] = {1,2,3};
	V v(a);

	using CV = hamon::ranges::common_view<hamon::views::all_t<V&>>;

	// views::common(v)
	{
		auto cv = hamon::views::common(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), a));
	}
	// v | views::common
	{
		auto cv = v | hamon::views::common;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using V = test_forward_common_range<int>;
	int a[] = {1,2,3};
	V v(a);

	using CV = hamon::views::all_t<V&>;

	// views::common(v)
	{
		auto cv = hamon::views::common(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), v.begin()));
	}
	// v | views::common
	{
		auto cv = v | hamon::views::common;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		VERIFY(legacy_equal(cv.begin(), cv.end(), v.begin()));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CommonViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace adaptor_test
}	// namespace common_view_test
}	// namespace hamon_ranges_test
