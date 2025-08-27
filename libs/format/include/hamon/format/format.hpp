/**
 *	@file	format.hpp
 *
 *	@brief	format の定義
 */

#ifndef HAMON_FORMAT_FORMAT_HPP
#define HAMON_FORMAT_FORMAT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format;

}	// namespace hamon

#else

#include <hamon/format/format_string.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/make_wformat_args.hpp>
#include <hamon/format/vformat.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/string.hpp>
#include <locale>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

template <typename... Args>
hamon::string
format(hamon::format_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/2
	return hamon::vformat(fmt.get(), hamon::make_format_args(args...));
}

template <typename... Args>
hamon::wstring
format(hamon::wformat_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/3
	return hamon::vformat(fmt.get(), hamon::make_wformat_args(args...));
}

template <typename... Args>
hamon::string
format(std::locale const& loc, hamon::format_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/4
	return hamon::vformat(loc, fmt.get(), hamon::make_format_args(args...));
}

template <typename... Args>
hamon::wstring
format(std::locale const& loc, hamon::wformat_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/5
	return hamon::vformat(loc, fmt.get(), hamon::make_wformat_args(args...));
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_HPP
