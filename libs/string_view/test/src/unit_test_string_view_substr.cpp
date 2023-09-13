/**
 *	@file	unit_test_string_view_substr.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

#if defined(HAMON_MSVC) && (HAMON_MSVC <= 1929) && !defined(NDEBUG)
// workaround: Visual Studio 2019 かつ Debugビルドのとき、実行時のテストだけ失敗してしまう
#  define HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(x)	\
	static_assert((x), "failed assertion : EXPECT_TRUE("#x")")
#else
#  define HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(x)	\
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(x)
#endif

TYPED_TEST(StringViewTest, SubStrTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;

	HAMON_CXX11_CONSTEXPR const auto str = StringViewTestHelper<CharT>::foo_bar();
	HAMON_CXX11_CONSTEXPR const string_view sv1{str};
	{
		HAMON_CXX11_CONSTEXPR const string_view sv2 = sv1.substr();
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv2.data() == str);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.length() == 7);
	}
	{
		HAMON_CXX11_CONSTEXPR const string_view sv2 = sv1.substr(2);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv2.data() == str + 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.length() == 5);
	}
	{
		HAMON_CXX11_CONSTEXPR const string_view sv2 = sv1.substr(2, 3);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv2.data() == str + 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.length() == 3);
	}
	{
		HAMON_CXX11_CONSTEXPR const string_view sv2 = sv1.substr(7, 10);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv2.data() == str + 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv2.length() == 0);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		EXPECT_THROW((void)sv1.substr(8), hamon::out_of_range);
	}
#endif
}

#undef HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE

}	// namespace string_view_test
}	// namespace hamon_test
