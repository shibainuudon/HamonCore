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
#include <string>

namespace hamon
{

// * hamon::ct::strlen
// strlenのconstexpr版です。
// std::strlenと違って、wchar_tやchar16_t等にも対応しています。
// 実行時の速度はそれほど速くない可能性があります。
// C++11のときは再帰で実装されているので、あまり長い文字列だとスタックオーバーフローになってしまいます。
// 
// * hamon::strlen
// strlenの非constexpr版です。
// std::strlenと違って、wchar_tやchar16_t等にも対応しています。
// 実行時の速度を重視して実装されています。
// C++20以上では、constexprの文脈で呼び出されるとconstexprになります。
//
// * まとめ
// コンパイル時に値を得たい場合は hamon::ct::strlen、
// 実行時に値を得たい場合は       hamon::strlen
// を使うと良いです。
// C++20以上だとどちらを呼び出しても同じです。

namespace detail
{

#if HAMON_CXX_STANDARD < 14

template <typename InputIterator>
inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen_ct_impl_2(InputIterator first, hamon::size_t n) HAMON_NOEXCEPT
{
	return *first ?
		strlen_ct_impl_2(first + 1, n + 1) :
		n;
}

template <typename InputIterator>
inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen_ct_impl(InputIterator first) HAMON_NOEXCEPT
{
	return strlen_ct_impl_2(first, 0);
}

#else

template <typename InputIterator>
inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen_ct_impl(InputIterator first) HAMON_NOEXCEPT
{
	hamon::size_t n = 0;
	
	while (*first++)
	{
		++n;
	}

	return n;
}

#endif

inline hamon::size_t
strlen_rt_impl(const char* str) HAMON_NOEXCEPT
{
	return std::strlen(str);
}

inline hamon::size_t
strlen_rt_impl(const wchar_t* str) HAMON_NOEXCEPT
{
	return std::wcslen(str);
}

#if defined(HAMON_HAS_CXX20_CHAR8_T)
inline hamon::size_t
strlen_rt_impl(char8_t const* str) HAMON_NOEXCEPT
{
	return std::char_traits<char8_t>::length(str);
}
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
inline hamon::size_t
strlen_rt_impl(char16_t const* str) HAMON_NOEXCEPT
{
	return std::char_traits<char16_t>::length(str);
}
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
inline hamon::size_t
strlen_rt_impl(char32_t const* str) HAMON_NOEXCEPT
{
	return std::char_traits<char32_t>::length(str);
}
#endif

}	// namespace detail

namespace ct
{

/**
 *	@brief		文字列の長さを得る
 *
 *	@param		str		ヌル終端された文字列へのポインタ
 *
 *	@return		文字列 str の長さ
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen(char const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_rt_impl(str);
	}
#endif
	return hamon::detail::strlen_ct_impl(str);
}

/**
 *	@overload
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen(wchar_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_rt_impl(str);
	}
#endif
	return hamon::detail::strlen_ct_impl(str);
}

/**
 *	@overload
 */
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen(char8_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_rt_impl(str);
	}
#endif
	return hamon::detail::strlen_ct_impl(str);
}
#endif

/**
 *	@overload
 */
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen(char16_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_rt_impl(str);
	}
#endif
	return hamon::detail::strlen_ct_impl(str);
}
#endif

/**
 *	@overload
 */
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
strlen(char32_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_rt_impl(str);
	}
#endif
	return hamon::detail::strlen_ct_impl(str);
}
#endif

}	// namespace ct

HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR hamon::size_t
strlen(char const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_ct_impl(str);
	}
#endif
	return hamon::detail::strlen_rt_impl(str);
}

/**
 *	@overload
 */
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR hamon::size_t
strlen(wchar_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_ct_impl(str);
	}
#endif
	return hamon::detail::strlen_rt_impl(str);
}

/**
 *	@overload
 */
#if defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR hamon::size_t
strlen(char8_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_ct_impl(str);
	}
#endif
	return hamon::detail::strlen_rt_impl(str);
}
#endif

/**
 *	@overload
 */
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR hamon::size_t
strlen(char16_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_ct_impl(str);
	}
#endif
	return hamon::detail::strlen_rt_impl(str);
}
#endif

/**
 *	@overload
 */
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_NODISCARD inline HAMON_CXX20_CONSTEXPR hamon::size_t
strlen(char32_t const* str) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (hamon::is_constant_evaluated())
	{
		return hamon::detail::strlen_ct_impl(str);
	}
#endif
	return hamon::detail::strlen_rt_impl(str);
}
#endif

}	// namespace hamon

#endif // HAMON_CSTRING_STRLEN_HPP
