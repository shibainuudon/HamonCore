/**
 *	@file	unit_test_string_view_ctor.cpp
 *
 *	@brief
 */

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "string_view_test_helper.hpp"

namespace hamon_test
{
namespace string_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if defined(HAMON_MSVC) && (HAMON_MSVC <= 1929) && !defined(NDEBUG)
// workaround: Visual Studio 2019 かつ Debugビルドのとき、実行時のテストだけ失敗してしまう
#  define HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(x)	\
	static_assert((x), "failed assertion : EXPECT_TRUE("#x")")
#else
#  define HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(x)	\
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(x)
#endif

TYPED_TEST(StringViewTest, CtorDefaultTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	{
		HAMON_CXX11_CONSTEXPR string_view sv;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.data()   == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.data()   == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.data()   == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
}

TYPED_TEST(StringViewTest, CtorCharPtrCountTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	{
		HAMON_CXX11_CONSTEXPR auto str = StringViewTestHelper<TypeParam>::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{str, 7};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 7);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == str);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR string_view sv{nullptr, 0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.data()   == nullptr);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR auto str = StringViewTestHelper<TypeParam>::with_nulls();
		HAMON_CXX11_CONSTEXPR string_view sv{str, 28};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 28);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 28);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == str);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
}

TYPED_TEST(StringViewTest, CtorCharPtrTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	{
		HAMON_CXX11_CONSTEXPR auto str = StringViewTestHelper<TypeParam>::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 7);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == str);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		HAMON_CXX11_CONSTEXPR auto str = StringViewTestHelper<TypeParam>::with_nulls();
		HAMON_CXX11_CONSTEXPR string_view sv{str};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 14);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 14);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == str);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
}

TYPED_TEST(StringViewTest, CtorRangeTest)
{
	using string_view = hamon::basic_string_view<TypeParam>;
	{
		HAMON_CXX11_CONSTEXPR auto str = StringViewTestHelper<TypeParam>::foo_bar();
		HAMON_CXX11_CONSTEXPR string_view sv{str, str + 3};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.length() == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.size()   == 3);
		HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE(sv.data() == str);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!sv.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(sv.max_size() >= sv.size());
	}
	{
		TypeParam arr[] = {'H', 'e', 'l', 'l', 'o', '\0', '!'};
		test_contiguous_range<TypeParam> rng(arr);
		string_view sv{rng};
		EXPECT_EQ(7, sv.length());
		EXPECT_TRUE(sv.data() == arr);
	}
}

TYPED_TEST(StringViewTest, CtorDeductionTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	using Helper = StringViewTestHelper<TypeParam>;
	{
		hamon::basic_string_view sv{Helper::abcd()};
		static_assert(hamon::is_same<decltype(sv), hamon::basic_string_view<TypeParam>>::value, "");
	}
	{
		hamon::basic_string_view sv{Helper::abcd(), 3};
		static_assert(hamon::is_same<decltype(sv), hamon::basic_string_view<TypeParam>>::value, "");
	}
	{
		auto str = Helper::abcd();
		hamon::basic_string_view sv{str, str + 2};
		static_assert(hamon::is_same<decltype(sv), hamon::basic_string_view<TypeParam>>::value, "");
	}
#endif
}

template <typename CharT>
inline HAMON_CXX14_CONSTEXPR bool CtorCopyTest()
{
	using string_view = hamon::basic_string_view<CharT>;
	{
		auto str = StringViewTestHelper<CharT>::foo_bar();
		string_view sv1{str, 7};
		string_view sv2{sv1};

		VERIFY(sv2.size()   == sv1.size());
		VERIFY(sv2.data()   == sv1.data());

		VERIFY(sv2.length() == 7);
		VERIFY(sv2.size()   == 7);
		VERIFY(sv2.data()   == str);
		VERIFY(!sv2.empty());
		VERIFY(sv2.max_size() >= sv2.size());
	}
	return true;
}

TYPED_TEST(StringViewTest, CtorCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorCopyTest<TypeParam>());
}

#undef HAMON_MSVC1929_WORKAROUND_EXPECT_TRUE
#undef VERIFY

}	// namespace string_view_test
}	// namespace hamon_test
