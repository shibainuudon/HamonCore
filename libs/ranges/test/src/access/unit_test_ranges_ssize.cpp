/**
 *	@file	unit_test_ranges_ssize.cpp
 *
 *	@brief	ranges::ssize のテスト
 */

#include <hamon/ranges/ssize.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace ssize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R
{
	HAMON_CXX14_CONSTEXPR int size() const noexcept { return 0; }
	HAMON_CXX14_CONSTEXPR R* begin() { return this; }
	HAMON_CXX14_CONSTEXPR R* end() { return this + 1; }
};

}	// namespace ssize_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true, hamon_ranges_test::ssize_test::R);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace ssize_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	constexpr int a[10]{ };
	static_assert(hamon::same_as_t<decltype(hamon::ranges::ssize(a)), std::ptrdiff_t>::value, "");
	static_assert(hamon::ranges::ssize(a) == 10, "");
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
	// MSVSの実装だとnoexcept指定されていない
	static_assert(noexcept(hamon::ranges::ssize(a)), "");
#endif

	int a2[2]{};
	static_assert(hamon::same_as_t<decltype(hamon::ranges::ssize(a2)), std::ptrdiff_t>::value, "");
	VERIFY(hamon::ranges::ssize(a2) == 2);
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
	static_assert(noexcept(hamon::ranges::ssize(a2)), "");
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[3]{ };
	test_sized_range<int, input_iterator_wrapper> ri(a);
	VERIFY(hamon::ranges::ssize(ri) == 3);
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
	static_assert(noexcept(hamon::ranges::ssize(ri)), "");
#endif

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[]{ 0, 1 };
	test_random_access_range<int> r(a);
	VERIFY(hamon::ranges::ssize(r) == hamon::ranges::end(r) - hamon::ranges::begin(r));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	R r;
	VERIFY(hamon::ranges::ssize(r) == 1);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
#if 0
	auto i = std::views::iota(1ull, 5u);
	auto s = hamon::ranges::size(i);
	auto ss = hamon::ranges::ssize(i);

	static_assert(hamon::same_as_t<decltype(ss), hamon::make_signed_t<decltype(s)>>::value, "");
	VERIFY(s == 4);
#endif

	return true;
}

GTEST_TEST(RangesTest, SSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

#undef VERIFY

}	// namespace ssize_test

}	// namespace hamon_ranges_test
