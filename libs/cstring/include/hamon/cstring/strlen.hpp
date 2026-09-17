/**
 *	@file	strlen.hpp
 *
 *	@brief	strlen 関数を定義
 */

#ifndef HAMON_CSTRING_STRLEN_HPP
#define HAMON_CSTRING_STRLEN_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cstring>
#include <cwchar>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR hamon::size_t
strlen_impl(T* s) HAMON_NOEXCEPT
{
	hamon::size_t n = 0;
	
	while (*s++)
	{
		++n;
	}

	return n;
}

}	// namespace detail

/**
 *	@brief		文字列の長さを得る
 *
 *	@param		s		ヌル終端された文字列へのポインタ
 *
 *	@return		文字列 s の長さ
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR
hamon::size_t strlen(char const* s) HAMON_NOEXCEPT
{
	if (!hamon::is_constant_evaluated())
	{
		return std::strlen(s);
	}

#if defined(HAMON_MSVC) || defined(HAMON_CLANG)
	return __builtin_strlen(s);
#else
	return hamon::detail::strlen_impl(s);
#endif
}

/**
 *	@overload
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR
hamon::size_t strlen(wchar_t const* s) HAMON_NOEXCEPT
{
	if (!hamon::is_constant_evaluated())
	{
		return std::wcslen(s);
	}

#if HAMON_HAS_BUILTIN(__builtin_wcslen) || defined(HAMON_MSVC)
	return __builtin_wcslen(s);
#else
	return hamon::detail::strlen_impl(s);
#endif
}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
/**
 *	@overload
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR
hamon::size_t strlen(char8_t const* s) HAMON_NOEXCEPT
{
#if defined(HAMON_MSVC)
	return __builtin_u8strlen(s);
#else
	return hamon::detail::strlen_impl(s);
#endif
}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
/**
 *	@overload
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR
hamon::size_t strlen(char16_t const* s) HAMON_NOEXCEPT
{
	return hamon::detail::strlen_impl(s);
}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
/**
 *	@overload
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR
hamon::size_t strlen(char32_t const* s) HAMON_NOEXCEPT
{
	return hamon::detail::strlen_impl(s);
}
#endif

}	// namespace hamon

#endif // HAMON_CSTRING_STRLEN_HPP
