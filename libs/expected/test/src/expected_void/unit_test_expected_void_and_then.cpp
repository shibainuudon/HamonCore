/**
 *	@file	unit_test_expected_void_and_then.cpp
 *
 *	@brief	and_then() のテスト
 *
 *	template<class F> constexpr auto and_then(F&& f) &;
 *	template<class F> constexpr auto and_then(F&& f) const &;
 *	template<class F> constexpr auto and_then(F&& f) &&;
 *	template<class F> constexpr auto and_then(F&& f) const &&;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/string.hpp>
#include <hamon/assert.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace and_then_test
{

template <typename E, typename F, typename = void>
struct has_and_then
	: hamon::false_type{};

template <typename E, typename F>
struct has_and_then<E, F, hamon::void_t<decltype(hamon::declval<E>().and_then(hamon::declval<F>()))>>
	: hamon::true_type{};

struct NonCopyable
{
	constexpr NonCopyable(int){}
	NonCopyable(NonCopyable const&) = delete;
	NonCopyable(NonCopyable&&) = default;
};

struct NonMovable
{
	constexpr NonMovable(int){}
	NonMovable(NonMovable const&) = delete;
	NonMovable(NonMovable&&) = delete;
};

hamon::expected<void, int> return_int() { return {}; }
hamon::expected<void, NonCopyable> return_noncopyable() { return {}; }
hamon::expected<void, NonMovable> return_nonmovable() { return {}; }

static_assert( has_and_then<hamon::expected<void, int        >      &, decltype(return_int)>::value, "");
static_assert(!has_and_then<hamon::expected<void, NonCopyable>      &, decltype(return_noncopyable)>::value, "");
static_assert( has_and_then<hamon::expected<void, int        > const&, decltype(return_int)>::value, "");
static_assert(!has_and_then<hamon::expected<void, NonCopyable> const&, decltype(return_noncopyable)>::value, "");
static_assert( has_and_then<hamon::expected<void, int       >      &&, decltype(return_int)>::value, "");
static_assert(!has_and_then<hamon::expected<void, NonMovable>      &&, decltype(return_nonmovable)>::value, "");
static_assert( has_and_then<hamon::expected<void, int       > const&&, decltype(return_int)>::value, "");
static_assert(!has_and_then<hamon::expected<void, NonMovable> const&&, decltype(return_nonmovable)>::value, "");

// [LWG 3877] https://cplusplus.github.io/LWG/issue3877, check constraint failing but not compile error inside the function body.
static_assert(!has_and_then<const hamon::expected<void, hamon::unique_ptr<int>>&, int()>::value, "");
static_assert(!has_and_then<const hamon::expected<void, hamon::unique_ptr<int>>&&, int()>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test_val_types()
{
	static_assert(hamon::is_void<Void>::value, "");

	struct F
	{
		constexpr hamon::expected<int, E>
		operator()() const
		{
			return 2;
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &      >().and_then(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const& >().and_then(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &&     >().and_then(f)), hamon::expected<int, E>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const&&>().and_then(f)), hamon::expected<int, E>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &      >().and_then(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const& >().and_then(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &&     >().and_then(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const&&>().and_then(f)), "");

	// Test & overload
	{
		hamon::expected<Void, E> v;
		auto val = v.and_then(f);
		VERIFY(val == 2);
	}

	// Test const& overload
	{
		hamon::expected<Void, E> const v;
		auto val = v.and_then(f);
		VERIFY(val == 2);
	}

	// Test && overload
	{
		hamon::expected<Void, E> v;
		auto val = hamon::move(v).and_then(f);
		VERIFY(val == 2);
	}

	// Test const&& overload
	{
		hamon::expected<Void, E> const v;
		auto val = hamon::move(v).and_then(f);
		VERIFY(val == 2);
	}
	return true;
}

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test_fail()
{
	static_assert(hamon::is_void<Void>::value, "");

	struct F
	{
		HAMON_CXX14_CONSTEXPR hamon::expected<int, E>
		operator()() const
		{
			HAMON_ASSERT(false);
			return 0;
		}
	} f;

	// Test & overload
	{
		hamon::expected<Void, E> v(hamon::unexpect, E{2});
		auto val = v.and_then(f);
		VERIFY(val.error() == E{2});
	}

	// Test const& overload
	{
		hamon::expected<Void, E> const v(hamon::unexpect, E{3});
		auto val = v.and_then(f);
		VERIFY(val.error() == E{3});
	}

	// Test && overload
	{
		hamon::expected<Void, E> v(hamon::unexpect, E{4});
		auto val = hamon::move(v).and_then(f);
		VERIFY(val.error() == E{4});
	}

	// Test const&& overload
	{
		hamon::expected<Void, E> const v(hamon::unexpect, E{5});
		auto val = hamon::move(v).and_then(f);
		VERIFY(val.error() == E{5});
	}
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::expected<void, hamon::string> ok()
{
	return {};
}

HAMON_CXX20_CONSTEXPR hamon::expected<void, hamon::string> ng()
{
	return hamon::unexpected<hamon::string>{"ng"};
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<void, hamon::string> v1;
	VERIFY(v1.and_then(ok).has_value());

	hamon::expected<void, hamon::string> v2;
	VERIFY(v2.and_then(ng).error() == "ng");

	hamon::expected<void, hamon::string> e1 = hamon::unexpected<hamon::string>{"empty"};
	VERIFY(e1.and_then(ng).error() == "empty");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, AndThenTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void const, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void const volatile, short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void const, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void volatile, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_val_types<void const volatile, long>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void const, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void volatile, long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void const volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void const, short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void volatile, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test_fail<void const volatile, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace and_then_test

}	// namespace hamon_expected_void_test
