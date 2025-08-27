/**
 *	@file	vformat.hpp
 *
 *	@brief	vformat の定義
 */

#ifndef HAMON_FORMAT_VFORMAT_HPP
#define HAMON_FORMAT_VFORMAT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::vformat;

}	// namespace hamon

#else

#include <hamon/format/format_args.hpp>
#include <hamon/format/wformat_args.hpp>
#include <hamon/format/vformat_to.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <locale>

namespace hamon
{

// 28.5.5 Formatting functions[format.functions]

inline hamon::string
vformat(hamon::string_view fmt, hamon::format_args args);

inline hamon::wstring
vformat(hamon::wstring_view fmt, hamon::wformat_args args);

inline hamon::string
vformat(std::locale const& loc, hamon::string_view fmt, hamon::format_args args);

inline hamon::wstring
vformat(std::locale const& loc, hamon::wstring_view fmt, hamon::wformat_args args);

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_VFORMAT_HPP
