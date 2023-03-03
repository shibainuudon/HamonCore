/**
 *	@file	unit_test_utility_forward_like.cpp
 *
 *	@brief	forward_like のテスト
 */

#include <hamon/utility/forward_like.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace forward_like_test
{

struct U {}; // class type so const-qualification is not stripped from a prvalue
using CU = const U;
using T  = int;
using CT = const T;

U u{};
const U& cu = u;

static_assert(hamon::is_same<decltype(hamon::forward_like<T>(U{})), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T>(CU{})), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T>(u)), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T>(cu)), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T>(std::move(u))), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T>(std::move(cu))), CU&&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward_like<CT>(U{})), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT>(CU{})), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT>(u)), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT>(cu)), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT>(std::move(u))), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT>(std::move(cu))), CU&&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward_like<T&>(U{})), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&>(CU{})), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&>(u)), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&>(cu)), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&>(std::move(u))), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&>(std::move(cu))), CU&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward_like<CT&>(U{})), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&>(CU{})), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&>(u)), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&>(cu)), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&>(std::move(u))), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&>(std::move(cu))), CU&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward_like<T&&>(U{})), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&&>(CU{})), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&&>(u)), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&&>(cu)), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&&>(std::move(u))), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&&>(std::move(cu))), CU&&>::value, "");

static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(U{})), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(CU{})), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(u)), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(cu)), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(std::move(u))), CU&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(std::move(cu))), CU&&>::value, "");

static_assert(noexcept(hamon::forward_like<T>(u)), "");

static_assert(hamon::is_same<decltype(hamon::forward_like<U&>(u)), U&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CU&>(cu)), CU&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<U&&>(std::move(u))), U&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CU&&>(std::move(cu))), CU&&>::value, "");

struct NoCtorCopyMove
{
	NoCtorCopyMove() = delete;
	NoCtorCopyMove(NoCtorCopyMove const&) = delete;
	NoCtorCopyMove(NoCtorCopyMove&&) = delete;
};

static_assert(hamon::is_same<decltype(hamon::forward_like<CT&&>(std::declval<NoCtorCopyMove>())), NoCtorCopyMove const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<CT&> (std::declval<NoCtorCopyMove>())), NoCtorCopyMove const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&&> (std::declval<NoCtorCopyMove>())), NoCtorCopyMove&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::forward_like<T&>  (std::declval<NoCtorCopyMove>())), NoCtorCopyMove&>::value, "");

static_assert(noexcept(hamon::forward_like<T>(std::declval<NoCtorCopyMove>())), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ForwardLikeTest()
{
	{
		int val       = 1729;
		auto&& result = hamon::forward_like<const double&>(val);
		static_assert(hamon::is_same<decltype(result), const int&>::value, "");
		VERIFY(&result == &val);
	}
	{
		int val       = 1729;
		auto&& result = hamon::forward_like<double&>(val);
		static_assert(hamon::is_same<decltype(result), int&>::value, "");
		VERIFY(&result == &val);
	}
	{
		int val       = 1729;
		auto&& result = hamon::forward_like<const double&&>(val);
		static_assert(hamon::is_same<decltype(result), const int&&>::value, "");
		VERIFY(&result == &val);
	}
	{
		int val       = 1729;
		auto&& result = hamon::forward_like<double&&>(val);
		static_assert(hamon::is_same<decltype(result), int&&>::value, "");
		VERIFY(&result == &val);
	}
	return true;
}

GTEST_TEST(UtilityTest, ForwardLikeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForwardLikeTest());
}

#undef VERIFY

}	// namespace forward_like_test

}	// namespace hamon_utility_test
