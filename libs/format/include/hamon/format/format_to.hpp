/**
 *	@file	format_to.hpp
 *
 *	@brief	format_to の定義
 */

#ifndef HAMON_FORMAT_FORMAT_TO_HPP
#define HAMON_FORMAT_FORMAT_TO_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_to;

}	// namespace hamon

#else

#include <hamon/format/format_string.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/format/vformat_to.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/make_wformat_args.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

template <hamon::output_iterator<char const&> Out, typename... Args>
Out format_to(Out out, hamon::format_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/8
	return hamon::vformat_to(hamon::move(out), fmt.get(), hamon::make_format_args(args...));
}

template <hamon::output_iterator<wchar_t const&> Out, typename... Args>
Out format_to(Out out, hamon::wformat_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/9
	return hamon::vformat_to(hamon::move(out), fmt.get(), hamon::make_wformat_args(args...));
}

template <hamon::output_iterator<char const&> Out, typename... Args>
Out format_to(Out out, std::locale const& loc, hamon::format_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/10
	return hamon::vformat_to(hamon::move(out), loc, fmt.get(), hamon::make_format_args(args...));
}

template <hamon::output_iterator<wchar_t const&> Out, typename... Args>
Out format_to(Out out, std::locale const& loc, hamon::wformat_string<Args...> fmt, Args&&... args)
{
	// [format.functions]/11
	return hamon::vformat_to(hamon::move(out), loc, fmt.get(), hamon::make_wformat_args(args...));
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_TO_HPP
