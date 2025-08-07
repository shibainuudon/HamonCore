/**
 *	@file	runtime_format.hpp
 *
 *	@brief	runtime_format の定義
 */

#ifndef HAMON_FORMAT_RUNTIME_FORMAT_HPP
#define HAMON_FORMAT_RUNTIME_FORMAT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::runtime_format;

}	// namespace hamon

#else

#include <hamon/format/detail/runtime_format_string.hpp>
#include <hamon/string_view.hpp>

namespace hamon
{

inline hamon::detail::runtime_format_string<char>
runtime_format(hamon::string_view fmt) noexcept
{
	return fmt;
}

inline hamon::detail::runtime_format_string<wchar_t>
runtime_format(hamon::wstring_view fmt) noexcept
{
	return fmt;
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_RUNTIME_FORMAT_HPP
