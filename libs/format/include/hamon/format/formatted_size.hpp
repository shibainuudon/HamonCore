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
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/make_wformat_args.hpp>
#include <hamon/format/other/__vformatted_size.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <locale>

namespace hamon
{

template <typename... Args>
hamon::size_t formatted_size(hamon::format_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformatted_size(fmt.get(), hamon::basic_format_args{ hamon::make_format_args(args...) });
}

template <typename... Args>
hamon::size_t formatted_size(hamon::wformat_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformatted_size(fmt.get(), hamon::basic_format_args{ hamon::make_wformat_args(args...) });
}

template <typename... Args>
hamon::size_t formatted_size(std::locale const& loc, hamon::format_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformatted_size(loc, fmt.get(), hamon::basic_format_args{ hamon::make_format_args(args...) });
}

template <typename... Args>
hamon::size_t formatted_size(std::locale const& loc, hamon::wformat_string<Args...> fmt, Args&&... args)
{
	return hamon::__vformatted_size(loc, fmt.get(), hamon::basic_format_args{ hamon::make_wformat_args(args...) });
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMATTED_SIZE_HPP
