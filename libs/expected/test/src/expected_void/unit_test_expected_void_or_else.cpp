/**
 *	@file	unit_test_expected_void_or_else.cpp
 *
 *	@brief	or_else() のテスト
 *
 *	template<class F> constexpr auto or_else(F&& f) &;
 *	template<class F> constexpr auto or_else(F&& f) const &;
 *	template<class F> constexpr auto or_else(F&& f) &&;
 *	template<class F> constexpr auto or_else(F&& f) const &&;
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

namespace or_else_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test_val_types()
{
	static_assert(hamon::is_void<Void>::value, "");

	struct F
	{
		constexpr hamon::expected<Void, int>
		operator()(E) const
		{
			return {};
		}
	} f;

	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &      >().or_else(f)), hamon::expected<Void, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const& >().or_else(f)), hamon::expected<Void, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> &&     >().or_else(f)), hamon::expected<Void, int>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::expected<Void, E> const&&>().or_else(f)), hamon::expected<Void, int>>::value, "");

	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &      >().or_else(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const& >().or_else(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> &&     >().or_else(f)), "");
	static_assert(!noexcept(hamon::declval<hamon::expected<Void, E> const&&>().or_else(f)), "");

	// Test & overload
	{
		hamon::expected<Void, E> v{hamon::unexpect};
		auto val = v.or_else(f);
		VERIFY(val.has_value());
	}

	// Test const& overload
	{
		hamon::expected<Void, E> const v{hamon::unexpect};
		auto val = v.or_else(f);
		VERIFY(val.has_value());
	}

	// Test && overload
	{
		hamon::expected<Void, E> v{hamon::unexpect};
		auto val = hamon::move(v).or_else(f);
		VERIFY(val.has_value());
	}

	// Test const&& overload
	{
		hamon::expected<Void, E> const v{hamon::unexpect};
		auto val = hamon::move(v).or_else(f);
		VERIFY(val.has_value());
	}
	return true;
}

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test_fail()
{
	static_assert(hamon::is_void<Void>::value, "");

	struct F
	{
		HAMON_CXX14_CONSTEXPR hamon::expected<Void, int>
		operator()(E) const
		{
			HAMON_ASSERT(false);
			return hamon::expected<Void, int>{hamon::unexpect};
		}
	} f;

	// Test & overload
	{
		hamon::expected<Void, E> v;
		auto val = v.or_else(f);
		VERIFY(val.has_value());
	}

	// Test const& overload
	{
		hamon::expected<Void, E> const v;
		auto val = v.or_else(f);
		VERIFY(val.has_value());
	}

	// Test && overload
	{
		hamon::expected<Void, E> v;
		auto val = hamon::move(v).or_else(f);
		VERIFY(val.has_value());
	}

	// Test const&& overload
	{
		hamon::expected<Void, E> const v;
		auto val = hamon::move(v).or_else(f);
		VERIFY(val.has_value());
	}
	return true;
}

HAMON_CXX20_CONSTEXPR hamon::expected<void, hamon::string> validate(int code)
{
	if (0 <= code)
	{
		return {};
	}
	else
	{
		return hamon::unexpected<hamon::string>{"bad code"};
	}
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	hamon::expected<void, int> v1;
	VERIFY(v1.or_else(validate).has_value());

	hamon::expected<void, int> e1 = hamon::unexpected<int>{42};
	VERIFY(e1.or_else(validate).has_value());

	hamon::expected<void, int> e2 = hamon::unexpected<int>{-100};
	VERIFY(e2.or_else(validate).error() == "bad code");

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, OrElseTest)
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

}	// namespace or_else_test

}	// namespace hamon_expected_void_test
