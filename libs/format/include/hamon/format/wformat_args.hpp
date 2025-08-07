/**
 *	@file	wformat_args.hpp
 *
 *	@brief	wformat_args の定義
 */

#ifndef HAMON_FORMAT_WFORMAT_ARGS_HPP
#define HAMON_FORMAT_WFORMAT_ARGS_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::wformat_args;

}	// namespace hamon

#else

#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/wformat_context.hpp>

namespace hamon
{

// [format.args], class template basic_format_args

using wformat_args = hamon::basic_format_args<hamon::wformat_context>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_WFORMAT_ARGS_HPP
