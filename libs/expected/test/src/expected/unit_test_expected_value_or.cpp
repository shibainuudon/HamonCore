/**
 *	@file	unit_test_expected_value_or.cpp
 *
 *	@brief	value_or() のテスト
 *
 *	template<class U = remove_cv_t<T>> constexpr T value_or(U&& v) const &;
 *	template<class U = remove_cv_t<T>> constexpr T value_or(U&& v) &&;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace value_or_test
{

#if !defined(HAMON_USE_STD_EXPECTED)
template <bool CopyNoexcept, bool ConvNoexcept>
struct S1
{
	S1(S1 const&) noexcept(CopyNoexcept) {}
	S1(int) noexcept(ConvNoexcept) {}
};

static_assert( noexcept(hamon::declval<hamon::expected<int, int> const&>().value_or(hamon::declval<int>())), "");
static_assert( noexcept(hamon::declval<hamon::expected<S1<true, true>, int> const&>().value_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<S1<true, false>, int> const&>().value_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<S1<false, true>, int> const&>().value_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<S1<false, false>, int> const&>().value_or(hamon::declval<int>())), "");

template <bool MoveNoexcept, bool ConvNoexcept>
struct S2
{
	S2(S2&&) noexcept(MoveNoexcept) {}
	S2(int) noexcept(ConvNoexcept) {}
};

static_assert( noexcept(hamon::declval<hamon::expected<int, int>&&>().value_or(hamon::declval<int>())), "");
static_assert( noexcept(hamon::declval<hamon::expected<S2<true, true>, int>&&>().value_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<S2<true, false>, int>&&>().value_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<S2<false, true>, int>&&>().value_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<S2<false, false>, int>&&>().value_or(hamon::declval<int>())), "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert( noexcept(hamon::declval<hamon::expected<T, E> &      >().value_or(hamon::declval<T>())), "");
	static_assert( noexcept(hamon::declval<hamon::expected<T, E> const& >().value_or(hamon::declval<T>())), "");
	static_assert( noexcept(hamon::declval<hamon::expected<T, E> &&     >().value_or(hamon::declval<T>())), "");
	static_assert( noexcept(hamon::declval<hamon::expected<T, E> const&&>().value_or(hamon::declval<T>())), "");
#endif
	{
		hamon::expected<T, E> const e{hamon::in_place, T{1}};
		auto&& x = e.value_or(T{10});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{1});
	}
	{
		hamon::expected<T, E> e{hamon::in_place, T{2}};
		auto&& x = e.value_or(T{20});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{2});
	}
	{
		hamon::expected<T, E> const e{hamon::in_place, T{3}};
		auto&& x = hamon::move(e).value_or(T{30});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{3});
	}
	{
		hamon::expected<T, E> e{hamon::in_place, T{4}};
		auto&& x = hamon::move(e).value_or(T{40});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{4});
	}
	{
		hamon::expected<T, E> const e{hamon::unexpect, E{1}};
		auto&& x = e.value_or(T{10});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{10});
	}
	{
		hamon::expected<T, E> e{hamon::unexpect, E{2}};
		auto&& x = e.value_or(T{20});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{20});
	}
	{
		hamon::expected<T, E> const e{hamon::unexpect, E{3}};
		auto&& x = hamon::move(e).value_or(T{30});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{30});
	}
	{
		hamon::expected<T, E> e{hamon::unexpect, E{4}};
		auto&& x = hamon::move(e).value_or(T{40});
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(x == T{40});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, ValueOrTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace value_or_test

}	// namespace hamon_expected_test
