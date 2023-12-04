/**
 *	@file	unit_test_ranges_subrange_structured_bindings.cpp
 *
 *	@brief
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace structured_bindings_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS)

// Visual Studio 2019/2022 で内部コンパイラエラーになってしまう
#if !(defined(HAMON_MSVC) && (HAMON_MSVC <= 1935))

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[4] = { 1,2,3,4 };
	auto r = hamon::ranges::subrange(a, a+4);
	static_assert(hamon::ranges::sized_range_t<decltype(r)>::value, "");
	{
		auto [first, last] = r;
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  int*>::value, "");
		VERIFY(first == a);
		VERIFY(last == a+4);
	}
	{
		auto [first, last] = hamon::move(r);
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  int*>::value, "");
		VERIFY(first == a);
		VERIFY(last == a+4);
	}
	{
		auto [first, last] = hamon::as_const(r);
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  int*>::value, "");
		VERIFY(first == a);
		VERIFY(last == a+4);
	}
	{
		auto [first, last] = hamon::move(hamon::as_const(r));
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  int*>::value, "");
		VERIFY(first == a);
		VERIFY(last == a+4);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[4] = { 1,2,3,4 };
	auto r = hamon::ranges::subrange(a, hamon::unreachable_sentinel);
	static_assert(!hamon::ranges::sized_range_t<decltype(r)>::value, "");
	{
		auto [first, last] = r;
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  hamon::unreachable_sentinel_t>::value, "");
		VERIFY(first == a);
		VERIFY(last != a+4);
	}
	{
		auto [first, last] = hamon::move(r);
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  hamon::unreachable_sentinel_t>::value, "");
		VERIFY(first == a);
		VERIFY(last != a+4);
	}
	{
		auto [first, last] = hamon::as_const(r);
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  hamon::unreachable_sentinel_t>::value, "");
		VERIFY(first == a);
		VERIFY(last != a+4);
	}
	{
		auto [first, last] = hamon::move(hamon::as_const(r));
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  hamon::unreachable_sentinel_t>::value, "");
		VERIFY(first == a);
		VERIFY(last != a+4);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[4] = { 1,2,3,4 };
	{
		auto r = hamon::ranges::subrange(a, a+4);
		auto&& [first, last] = r;
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  int*>::value, "");
		VERIFY(first == a);
		VERIFY(last == a+4);
		VERIFY(r.begin() == a);
		VERIFY(r.end() == a+4);
		first = a+2;
		last = a+2;
#if !defined(HAMON_MSVC)
		VERIFY(first == a+2);
		VERIFY(last == a+2);
#endif
		VERIFY(r.begin() == a);
		VERIFY(r.end() == a+4);
	}
	{
		auto const r = hamon::ranges::subrange(a, a+4);
		auto&& [first, last] = r;
		static_assert(hamon::is_same<decltype(first), int*>::value, "");
		static_assert(hamon::is_same<decltype(last),  int*>::value, "");
		VERIFY(first == a);
		VERIFY(last == a+4);
		VERIFY(r.begin() == a);
		VERIFY(r.end() == a+4);
		first = a+2;
		last = a+2;
#if !defined(HAMON_MSVC)
		VERIFY(first == a+2);
		VERIFY(last == a+2);
#endif
		VERIFY(r.begin() == a);
		VERIFY(r.end() == a+4);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeStructuredBindingsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#endif	// !(defined(HAMON_MSVC) && (HAMON_MSVC <= 1935))

#endif	// defined(HAMON_HAS_CXX17_STRUCTURED_BINDINGS)

#undef VERIFY

}	// namespace structured_bindings_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
