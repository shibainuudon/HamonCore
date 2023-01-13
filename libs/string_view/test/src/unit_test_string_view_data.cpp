/**
 *	@file	unit_test_string_view_data.cpp
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

#if defined(HAMON_MSVC) && (HAMON_MSVC <= 1929) && !defined(NDEBUG)
// workaround: Visual Studio 2019 かつ Debugビルドのとき、実行時のテストだけ失敗してしまう
#  define HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(x)	\
	static_assert((x), "failed assertion : EXPECT_TRUE("#x")")
#else
#  define HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(x)	\
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(x)
#endif

TYPED_TEST(StringViewTest, DataTest)
{
	using CharT = TypeParam;
	using string_view = hamon::basic_string_view<CharT>;
	using Helper = StringViewTestHelper<CharT>;

	{
		HAMON_CXX11_CONSTEXPR auto p = Helper::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{p};
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == p);
	}
	{
		HAMON_CXX11_CONSTEXPR auto p = Helper::aababc();
		HAMON_CXX11_CONSTEXPR string_view sv{p, 1};
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == p);
	}
	{
		HAMON_CXX11_CONSTEXPR auto p = Helper::abcd();
		HAMON_CXX11_CONSTEXPR string_view sv{p};
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == p);
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.data() == nullptr);
	}
}

#undef HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE

}	// namespace string_view_test
}	// namespace hamon_test
