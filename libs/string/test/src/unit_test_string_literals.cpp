/**
 *	@file	unit_test_string_literals.cpp
 *
 *	@brief	ユーザー定義リテラルのテスト
 *
 *	constexpr string    operator""s(const char* str, size_t len);
 *	constexpr u8string  operator""s(const char8_t* str, size_t len);
 *	constexpr u16string operator""s(const char16_t* str, size_t len);
 *	constexpr u32string operator""s(const char32_t* str, size_t len);
 *	constexpr wstring   operator""s(const wchar_t* str, size_t len);
 */

#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"

namespace hamon_test
{
namespace string_test
{
namespace literals_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using namespace hamon::literals::string_literals;
		auto s1 = "hello"_s;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		auto s2 = u8"hello"_s;
#endif
		auto s3 = u"hello"_s;
		auto s4 = U"hello"_s;
		auto s5 = L"hello"_s;
		static_assert(hamon::is_same<decltype(s1), hamon::string>::value, "");
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		static_assert(hamon::is_same<decltype(s2), hamon::u8string>::value, "");
#endif
		static_assert(hamon::is_same<decltype(s3), hamon::u16string>::value, "");
		static_assert(hamon::is_same<decltype(s4), hamon::u32string>::value, "");
		static_assert(hamon::is_same<decltype(s5), hamon::wstring>::value, "");
		VERIFY(s1 == hamon::string("hello"));
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		VERIFY(s2 == hamon::u8string(u8"hello"));
#endif
		VERIFY(s3 == hamon::u16string(u"hello"));
		VERIFY(s4 == hamon::u32string(U"hello"));
		VERIFY(s5 == hamon::wstring(L"hello"));
	}
	{
		using namespace hamon::string_literals;
		static_assert(hamon::is_same<decltype("hello"_s), hamon::string>::value, "");
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		static_assert(hamon::is_same<decltype(u8"hello"_s), hamon::u8string>::value, "");
#endif
		static_assert(hamon::is_same<decltype(u"hello"_s), hamon::u16string>::value, "");
		static_assert(hamon::is_same<decltype(U"hello"_s), hamon::u32string>::value, "");
		static_assert(hamon::is_same<decltype(L"hello"_s), hamon::wstring>::value, "");
	}
	{
		using namespace hamon::literals;
		static_assert(hamon::is_same<decltype("hello"_s), hamon::string>::value, "");
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		static_assert(hamon::is_same<decltype(u8"hello"_s), hamon::u8string>::value, "");
#endif
		static_assert(hamon::is_same<decltype(u"hello"_s), hamon::u16string>::value, "");
		static_assert(hamon::is_same<decltype(U"hello"_s), hamon::u32string>::value, "");
		static_assert(hamon::is_same<decltype(L"hello"_s), hamon::wstring>::value, "");
	}
	{
		using namespace hamon;
		static_assert(hamon::is_same<decltype("hello"_s), hamon::string>::value, "");
#if defined(HAMON_HAS_CXX20_CHAR8_T)
		static_assert(hamon::is_same<decltype(u8"hello"_s), hamon::u8string>::value, "");
#endif
		static_assert(hamon::is_same<decltype(u"hello"_s), hamon::u16string>::value, "");
		static_assert(hamon::is_same<decltype(U"hello"_s), hamon::u32string>::value, "");
		static_assert(hamon::is_same<decltype(L"hello"_s), hamon::wstring>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(StringTest, LiteralsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace literals_test
}	// namespace string_test
}	// namespace hamon_test
