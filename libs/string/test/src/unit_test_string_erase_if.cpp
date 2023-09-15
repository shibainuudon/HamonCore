/**
 *	@file	unit_test_string_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/string/erase_if.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>

namespace hamon_string_test
{

namespace erase_if_test
{

template <typename CharT>
struct StringTestHelper;

template <>
struct StringTestHelper<char>
{
	HAMON_CONSTEXPR static const char* abbccc() { return "abbccc"; }
	HAMON_CONSTEXPR static const char* abcde() { return "abcde"; }
	HAMON_CONSTEXPR static const char* abb() { return "abb"; }
	HAMON_CONSTEXPR static const char* bcde() { return "bcde"; }
};

template <>
struct StringTestHelper<wchar_t>
{
	HAMON_CONSTEXPR static const wchar_t* abbccc() { return L"abbccc"; }
	HAMON_CONSTEXPR static const wchar_t* abcde() { return L"abcde"; }
	HAMON_CONSTEXPR static const wchar_t* abb() { return L"abb"; }
	HAMON_CONSTEXPR static const wchar_t* bcde() { return L"bcde"; }
};

#if defined(HAMON_HAS_CXX20_CHAR8_T)
template <>
struct StringTestHelper<char8_t>
{
	HAMON_CONSTEXPR static const char8_t* abbccc() { return u8"abbccc"; }
	HAMON_CONSTEXPR static const char8_t* abcde() { return u8"abcde"; }
	HAMON_CONSTEXPR static const char8_t* abb() { return u8"abb"; }
	HAMON_CONSTEXPR static const char8_t* bcde() { return u8"bcde"; }
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
template <>
struct StringTestHelper<char16_t>
{
	HAMON_CONSTEXPR static const char16_t* abbccc() { return u"abbccc"; }
	HAMON_CONSTEXPR static const char16_t* abcde() { return u"abcde"; }
	HAMON_CONSTEXPR static const char16_t* abb() { return u"abb"; }
	HAMON_CONSTEXPR static const char16_t* bcde() { return u"bcde"; }
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
template <>
struct StringTestHelper<char32_t>
{
	HAMON_CONSTEXPR static const char32_t* abbccc() { return U"abbccc"; }
	HAMON_CONSTEXPR static const char32_t* abcde() { return U"abcde"; }
	HAMON_CONSTEXPR static const char32_t* abb() { return U"abb"; }
	HAMON_CONSTEXPR static const char32_t* bcde() { return U"bcde"; }
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;
	{
		string s = Helper::abcde();
		auto r = hamon::erase_if(s, [](CharT c) { return c == Helper::abcde()[0]; });	// 'a'
		VERIFY(s == Helper::bcde());
		VERIFY(r == 1);
	}
	{
		string s = Helper::abbccc();
		auto r = hamon::erase_if(s, [](CharT c) { return c == Helper::abcde()[2]; });	// 'c'
		VERIFY(s == Helper::abb());
		VERIFY(r == 3);
	}
	{
		string s = Helper::abbccc();
		auto r = hamon::erase_if(s, [](CharT c) { return c == Helper::abcde()[3]; });	// 'd'
		VERIFY(s == Helper::abbccc());
		VERIFY(r == 0);
	}
	return true;
}

GTEST_TEST(StringTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest<char>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest<wchar_t>());
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest<char8_t>());
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest<char16_t>());
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest<char32_t>());
#endif
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace hamon_string_test
