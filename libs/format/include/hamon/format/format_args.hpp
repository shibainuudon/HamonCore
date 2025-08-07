/**
 *	@file	format_args.hpp
 *
 *	@brief	format_args の定義
 */

#ifndef HAMON_FORMAT_FORMAT_ARGS_HPP
#define HAMON_FORMAT_FORMAT_ARGS_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_args;

}	// namespace hamon

#else

#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/format_context.hpp>

namespace hamon
{

// [format.args], class template basic_format_args

using format_args = hamon::basic_format_args<hamon::format_context>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_ARGS_HPP
