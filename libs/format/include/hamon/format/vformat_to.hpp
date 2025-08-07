/**
 *	@file	vformat_to.hpp
 *
 *	@brief	vformat_to の定義
 */

#ifndef HAMON_FORMAT_VFORMAT_TO_HPP
#define HAMON_FORMAT_VFORMAT_TO_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::vformat_to;

}	// namespace hamon

#else

#include <hamon/format/format_args.hpp>
#include <hamon/format/wformat_args.hpp>
#include <hamon/string_view.hpp>
#include <locale>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

template <typename Out>
Out vformat_to(Out out, hamon::string_view fmt, hamon::format_args args);
template <typename Out>
Out vformat_to(Out out, hamon::wstring_view fmt, hamon::wformat_args args);
template <typename Out>
Out vformat_to(Out out, std::locale const& loc, hamon::string_view fmt, hamon::format_args args);
template <typename Out>
Out vformat_to(Out out, std::locale const& loc, hamon::wstring_view fmt, hamon::wformat_args args);

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_VFORMAT_TO_HPP
