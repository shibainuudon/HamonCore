/**
 *	@file	unit_test_string_view_compare_operator.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, CompareOperatorTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;
	{
		HAMON_CXX11_CONSTEXPR string_view const sv1{ Helper::aababc(), 6 };	// "aababc"
		HAMON_CXX11_CONSTEXPR string_view const sv2 = sv1;					// "aababc"
		HAMON_CXX11_CONSTEXPR string_view const sv3 = sv1.substr(0, 5);		// "aabab"
		HAMON_CXX11_CONSTEXPR string_view const sv4 = sv1.substr(1, 5);		// "ababc"

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 == sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 == sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 == sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 == sv4));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 != sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 != sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 != sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 != sv4));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <  sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <  sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <  sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <  sv4));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >  sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >  sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >  sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >  sv4));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <= sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <= sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <= sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <= sv4));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >= sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >= sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >= sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >= sv4));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(sv1 <=> sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(sv1 <=> sv2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(sv1 <=> sv3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(sv1 <=> sv4));
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR string_view const sv1{ Helper::abcd() };	// "abcd"
		HAMON_CXX11_CONSTEXPR CharT const* s1 = Helper::abcd();			// "abcd"
		HAMON_CXX11_CONSTEXPR CharT const* s2 = Helper::aababc();		// "aababc"
		HAMON_CXX11_CONSTEXPR CharT const* s3 = Helper::cd();			// "cd"

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 == s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 == s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 == s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 != s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 != s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 != s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <  s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <  s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <  s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >  s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >  s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >  s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <= s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 <= s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 <= s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >= s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (sv1 >= s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(sv1 >= s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s1 == sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s2 == sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s3 == sv1));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s1 != sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s2 != sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s3 != sv1));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s1 <  sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s2 <  sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s3 <  sv1));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s1 >  sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s2 >  sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s3 >  sv1));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s1 <= sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s2 <= sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s3 <= sv1));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s1 >= sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(s2 >= sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (s3 >= sv1));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(sv1 <=> s1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(sv1 <=> s2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(sv1 <=> s3));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(s1 <=> sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(s2 <=> sv1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(s3 <=> sv1));
#endif
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
