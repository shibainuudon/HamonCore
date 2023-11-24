/**
 *	@file	unit_test_string_view_compare.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

TYPED_TEST(StringViewTest, CompareTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;

	HAMON_CXX11_CONSTEXPR auto const str = StringViewTestHelper<CharT>::foo_bar();
	HAMON_CXX11_CONSTEXPR string_view const sv1{str, 7};
	HAMON_CXX11_CONSTEXPR string_view const sv2{str, 6};
	HAMON_CXX11_CONSTEXPR string_view const sv3{str, 6};
	HAMON_CXX11_CONSTEXPR string_view const sv4{str, 5};
	HAMON_CXX11_CONSTEXPR string_view const sv5{str + 1, 2};
	HAMON_CXX11_CONSTEXPR string_view const sv6{str + 1, 3};
	HAMON_CXX11_CONSTEXPR string_view const sv7{str + 1, 3};
	HAMON_CXX11_CONSTEXPR string_view const sv8{str + 1, 4};

	// (1)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv1) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv2) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv3) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv4) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv5) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv6) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv7) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.compare(sv8) <  0);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv1) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv2) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv3) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv4) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv5) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv6) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv7) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv6.compare(sv8) <  0);

	// (2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 8, sv1) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 6, sv1) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 3, sv1) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 6, sv2) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 3, sv6) == 0);

	// (3)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 7, sv1, 0, 7) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 6, sv1, 0, 6) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 7, sv1, 0, 8) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 6, sv1, 0, 7) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 7, sv1, 0, 6) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 6, sv1, 0, 6) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 6, sv1, 1, 6) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(2, 2, sv6, 1, 2) == 0);

	// (4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(str) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(str + 1) < 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(str + 4) > 0);

	// (5)
#if !(defined(HAMON_CLANG) && 150000 <= HAMON_CLANG && HAMON_CLANG < 160000 && HAMON_CXX_STANDARD == 20)
	// clang-15, C++20, Release, 実行時 の組み合わせのときのみ、以下のテストが失敗する
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 7, str + 1) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 6, str + 1) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 5, str + 1) <  0);
#endif
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 5, str)     >  0);

	// (6)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 6, str + 1, 6) == 0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 5, str + 1, 6) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 6, str + 1, 5) >  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(0, 6, str + 1, 6) <  0);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv1.compare(1, 6, str + 0, 6) >  0);
}

}	// namespace string_view_test
}	// namespace hamon_test
