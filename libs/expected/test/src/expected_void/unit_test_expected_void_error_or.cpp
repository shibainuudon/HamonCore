/**
 *	@file	unit_test_expected_void_error_or.cpp
 *
 *	@brief	error_or() のテスト
 *
 *	template<class G = E> constexpr E error_or(G&& e) const &;
 *	template<class G = E> constexpr E error_or(G&& e) &&;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace error_or_test
{

#if !defined(HAMON_USE_STD_EXPECTED)
template <bool CopyNoexcept, bool ConvNoexcept>
struct S1
{
	S1(S1 const&) noexcept(CopyNoexcept) {}
	S1(int) noexcept(ConvNoexcept) {}
};

static_assert( noexcept(hamon::declval<hamon::expected<void, int> const&>().error_or(hamon::declval<int>())), "");
static_assert( noexcept(hamon::declval<hamon::expected<void, S1<true, true>> const&>().error_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<void, S1<true, false>> const&>().error_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<void, S1<false, true>> const&>().error_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<void, S1<false, false>> const&>().error_or(hamon::declval<int>())), "");

template <bool MoveNoexcept, bool ConvNoexcept>
struct S2
{
	S2(S2&&) noexcept(MoveNoexcept) {}
	S2(int) noexcept(ConvNoexcept) {}
};

static_assert( noexcept(hamon::declval<hamon::expected<void, int>&&>().error_or(hamon::declval<int>())), "");
static_assert( noexcept(hamon::declval<hamon::expected<void, S2<true, true>>&&>().error_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<void, S2<true, false>>&&>().error_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<void, S2<false, true>>&&>().error_or(hamon::declval<int>())), "");
static_assert(!noexcept(hamon::declval<hamon::expected<void, S2<false, false>>&&>().error_or(hamon::declval<int>())), "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert( noexcept(hamon::declval<hamon::expected<Void, E> &      >().error_or(hamon::declval<E>())), "");
	static_assert( noexcept(hamon::declval<hamon::expected<Void, E> const& >().error_or(hamon::declval<E>())), "");
	static_assert( noexcept(hamon::declval<hamon::expected<Void, E> &&     >().error_or(hamon::declval<E>())), "");
	static_assert( noexcept(hamon::declval<hamon::expected<Void, E> const&&>().error_or(hamon::declval<E>())), "");
#endif
	{
		hamon::expected<Void, E> const e{hamon::in_place};
		auto&& x = e.error_or(E{10});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{10});
	}
	{
		hamon::expected<Void, E> e{hamon::in_place};
		auto&& x = e.error_or(E{20});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{20});
	}
	{
		hamon::expected<Void, E> const e{hamon::in_place};
		auto&& x = hamon::move(e).error_or(E{30});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{30});
	}
	{
		hamon::expected<Void, E> e{hamon::in_place};
		auto&& x = hamon::move(e).error_or(E{40});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{40});
	}
	{
		hamon::expected<Void, E> const e{hamon::unexpect, E{1}};
		auto&& x = e.error_or(E{10});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{1});
	}
	{
		hamon::expected<Void, E> e{hamon::unexpect, E{2}};
		auto&& x = e.error_or(E{20});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{2});
	}
	{
		hamon::expected<Void, E> const e{hamon::unexpect, E{3}};
		auto&& x = hamon::move(e).error_or(E{30});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{3});
	}
	{
		hamon::expected<Void, E> e{hamon::unexpect, E{4}};
		auto&& x = hamon::move(e).error_or(E{40});
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{4});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, ErrorOrTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, float>()));
}

}	// namespace error_or_test

}	// namespace hamon_expected_void_test
