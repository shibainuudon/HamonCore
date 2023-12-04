/**
 *	@file	unit_test_variant_holds_alternative.cpp
 *
 *	@brief	holds_alternative<T>(v) のテスト
 *
 *	template<class T, class... Types>
 *	constexpr bool holds_alternative(const variant<Types...>& v) noexcept;
 */

#include <hamon/variant/holds_alternative.hpp>
#include <hamon/variant/variant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_variant_test
{

namespace holds_alternative_test
{

GTEST_TEST(VariantTest, HoldsAlternativeTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int> v(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::holds_alternative<int>(v));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::holds_alternative<int>(v));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const long> v(
			hamon::in_place_index_t<0>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::holds_alternative<int>(v));
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::holds_alternative<const long>(v));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::holds_alternative<int>(v));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::holds_alternative<const long>(v));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, const long> v(
			hamon::in_place_index_t<1>{}, 42);
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::holds_alternative<int>(v));
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::holds_alternative<const long>(v));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::holds_alternative<int>(v));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::holds_alternative<const long>(v));
	}
}

}	// namespace holds_alternative_test

}	// namespace hamon_variant_test
