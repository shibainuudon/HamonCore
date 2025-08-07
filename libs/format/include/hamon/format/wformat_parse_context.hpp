/**
 *	@file	wformat_parse_context.hpp
 *
 *	@brief	wformat_parse_context の定義
 */

#ifndef HAMON_FORMAT_WFORMAT_PARSE_CONTEXT_HPP
#define HAMON_FORMAT_WFORMAT_PARSE_CONTEXT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::wformat_parse_context;

}	// namespace hamon

#else

#include <hamon/format/basic_format_parse_context.hpp>

namespace hamon
{

// [format.parse.ctx], class template basic_format_parse_context
using wformat_parse_context = hamon::basic_format_parse_context<wchar_t>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_WFORMAT_PARSE_CONTEXT_HPP
