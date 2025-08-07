/**
 *	@file	formatted_size.hpp
 *
 *	@brief	formatted_size の定義
 */

#ifndef HAMON_FORMAT_FORMATTED_SIZE_HPP
#define HAMON_FORMAT_FORMATTED_SIZE_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::formatted_size;

}	// namespace hamon

#else

#include <hamon/format/format_string.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <locale>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

template <typename... Args>
hamon::size_t formatted_size(hamon::format_string<Args...> fmt, Args&&... args);

template <typename... Args>
hamon::size_t formatted_size(hamon::wformat_string<Args...> fmt, Args&&... args);

template <typename... Args>
hamon::size_t formatted_size(std::locale const& loc, hamon::format_string<Args...> fmt, Args&&... args);

template <typename... Args>
hamon::size_t formatted_size(std::locale const& loc, hamon::wformat_string<Args...> fmt, Args&&... args);

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMATTED_SIZE_HPP
