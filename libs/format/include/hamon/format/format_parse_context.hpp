/**
 *	@file	format_parse_context.hpp
 *
 *	@brief	format_parse_context の定義
 */

#ifndef HAMON_FORMAT_FORMAT_PARSE_CONTEXT_HPP
#define HAMON_FORMAT_FORMAT_PARSE_CONTEXT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_parse_context;

}	// namespace hamon

#else

#include <hamon/format/basic_format_parse_context.hpp>

namespace hamon
{

// [format.parse.ctx], class template basic_format_parse_context
using format_parse_context = hamon::basic_format_parse_context<char>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_PARSE_CONTEXT_HPP
