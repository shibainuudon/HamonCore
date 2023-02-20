/**
 *	@file	unit_test_variant_valueless_by_exception.cpp
 *
 *	@brief	constexpr bool valueless_by_exception() const noexcept; のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace valueless_by_exception_test
{

GTEST_TEST(VariantTest, ValuelessByExceptionTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v.valueless_by_exception());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v(
			hamon::in_place_index_t<1>{}, 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v.valueless_by_exception());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		struct S { operator int() { throw 42; } };
		hamon::variant<float, int> v{12.f};
		EXPECT_FALSE(v.valueless_by_exception());
		EXPECT_THROW(v.emplace<1>(S()), int);
#if !defined(HAMON_USE_STD_VARIANT)
		EXPECT_TRUE(v.valueless_by_exception());
#endif
	}
#endif
}

}	// namespace valueless_by_exception_test

}	// namespace hamon_variant_test
