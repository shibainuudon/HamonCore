/**
 *	@file	unit_test_variant_index.cpp
 *
 *	@brief	size_t index() const のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace index_test
{

GTEST_TEST(VariantTest, IndexTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, v.index());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::variant<int, long> v(
			hamon::in_place_index_t<1>{}, 43);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, v.index());
	}
	{
		hamon::variant<char, float, std::string> v("hoge");
		EXPECT_EQ(2u, v.index());
		v = 0.5f;
		EXPECT_EQ(1u, v.index());
		v.emplace<char>();
		EXPECT_EQ(0u, v.index());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		struct S { operator int() { throw 42; } };
		hamon::variant<float, int> v{12.f};
		EXPECT_EQ(0u, v.index());
		EXPECT_THROW(v.emplace<1>(S()), int);
#if !defined(HAMON_USE_STD_VARIANT)
		EXPECT_EQ(hamon::variant_npos, v.index());
#endif
	}
#endif
}

}	// namespace index_test

}	// namespace hamon_variant_test
