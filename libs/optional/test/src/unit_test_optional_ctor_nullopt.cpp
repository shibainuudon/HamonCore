/**
 *	@file	unit_test_optional_ctor_nullopt.cpp
 *
 *	@brief	nullopt_tを引数に取るコンストラクタのテスト
 *
 *	constexpr optional(nullopt_t) noexcept;
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_nullopt_test
{

struct NoConstexprDefaultCtor
{
	NoConstexprDefaultCtor() {}
};

struct NoDefaultCtor
{
	NoDefaultCtor() = delete;
};

GTEST_TEST(OptionalTest, CtorNulloptTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = hamon::nullopt;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o{ hamon::nullopt };
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int> o = { hamon::nullopt };
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}

	// [optional.ctor]/3
	// For every object type T these constructors are constexpr constructors
	{
#if defined(HAMON_CLANG) ||	\
	(defined(HAMON_GCC_VERSION) && HAMON_GCC_VERSION < 100000)
		hamon::optional<NoConstexprDefaultCtor> o = hamon::nullopt;
		EXPECT_FALSE(o.has_value());
#else
		HAMON_CXX20_CONSTEXPR hamon::optional<NoConstexprDefaultCtor> o = hamon::nullopt;
		HAMON_CXX20_CONSTEXPR_EXPECT_FALSE(o.has_value());
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<NoDefaultCtor> o = hamon::nullopt;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o.has_value());
	}
}

}	// namespace ctor_nullopt_test

}	// namespace hamon_optional_test
