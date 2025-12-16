/**
 *	@file	literals.hpp
 *
 *	@brief	ユーザー定義リテラル
 */

#ifndef HAMON_STRING_LITERALS_HPP
#define HAMON_STRING_LITERALS_HPP

#include <hamon/string/typedefs.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

// 23.4.7 Suffix for basic_string literals[basic.string.literals]

namespace hamon {
inline namespace literals {
inline namespace string_literals {

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(5311)	// '演算子文字列-リテラル識別子' の形式のリテラル演算子 ID は非推奨になりました

// アンダースコアで始まらないユーザー定義リテラルのサフィックス名は、
// 標準C++の将来の拡張のために予約されているため、アンダースコアから始まる名前に変更した。

// [basic.string.literals], suffix for basic_string literals
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR	// nodiscard as an extension
hamon::string operator"" _s(const char* str, hamon::size_t len)
{
	// [basic.string.literals]/1
	return hamon::string{str, len};
}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR	// nodiscard as an extension
hamon::u8string operator"" _s(const char8_t* str, hamon::size_t len)
{
	// [basic.string.literals]/2
	return hamon::u8string{str, len};
}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR	// nodiscard as an extension
hamon::u16string operator"" _s(const char16_t* str, hamon::size_t len)
{
	// [basic.string.literals]/3
	return hamon::u16string{str, len};
}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR	// nodiscard as an extension
hamon::u32string operator"" _s(const char32_t* str, hamon::size_t len)
{
	// [basic.string.literals]/4
	return hamon::u32string{str, len};
}
#endif

HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR	// nodiscard as an extension
hamon::wstring operator"" _s(const wchar_t* str, hamon::size_t len)
{
	// [basic.string.literals]/5
	return hamon::wstring{str, len};
}

HAMON_WARNING_POP()

}	// inline namespace string_literals
}	// inline namespace literals
}	// namespace hamon

#endif // HAMON_STRING_LITERALS_HPP
