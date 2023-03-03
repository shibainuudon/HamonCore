/**
 *	@file	unit_test_string_view_literals.cpp
 *
 *	@brief
 */

#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_test
{
namespace string_view_test
{

GTEST_TEST(StringViewTest, LiteralsTest)
{
	{
		using namespace hamon::literals;
		HAMON_CXX11_CONSTEXPR auto sv = "abcd"_sv;
		static_assert(hamon::is_same<decltype(sv), hamon::string_view const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv == "abcd");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != "ab");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != "cd");
	}
	{
		using namespace hamon::literals::string_view_literals;
		HAMON_CXX11_CONSTEXPR auto sv = L"abcd"_sv;
		static_assert(hamon::is_same<decltype(sv), hamon::wstring_view const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv == L"abcd");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != L"ab");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != L"cd");
	}
	{
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		using namespace hamon::literals;
		HAMON_CXX11_CONSTEXPR auto sv = u8"abcd"_sv;
		static_assert(hamon::is_same<decltype(sv), hamon::u8string_view const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv == u8"abcd");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != u8"ab");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != u8"cd");
#endif
	}
	{
#if defined(HAMON_HAS_CXX11_CHAR16_T)
		using namespace hamon::literals::string_view_literals;
		HAMON_CXX11_CONSTEXPR auto sv = u"abcd"_sv;
		static_assert(hamon::is_same<decltype(sv), hamon::u16string_view const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv == u"abcd");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != u"ab");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != u"cd");
#endif
	}
	{
#if defined(HAMON_HAS_CXX11_CHAR32_T)
		using namespace hamon::string_view_literals;
		HAMON_CXX11_CONSTEXPR auto sv = U"abcd"_sv;
		static_assert(hamon::is_same<decltype(sv), hamon::u32string_view const>::value, "");

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv == U"abcd");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != U"ab");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv != U"cd");
#endif
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
