/**
 *	@file	make_wformat_args.hpp
 *
 *	@brief	make_wformat_args の定義
 */

#ifndef HAMON_FORMAT_MAKE_WFORMAT_ARGS_HPP
#define HAMON_FORMAT_MAKE_WFORMAT_ARGS_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::make_wformat_args;

}	// namespace hamon

#else

#include <hamon/format/detail/format_arg_store.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/format/make_format_args.hpp>

namespace hamon
{

// 28.5.8.2 Class template format-arg-store[format.arg.store]

template <typename... Args>
hamon::detail::format_arg_store<hamon::wformat_context, Args...>
make_wformat_args(Args&... args)
{
	// [format.arg.store]/4
	return hamon::make_format_args<hamon::wformat_context>(args...);
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_MAKE_WFORMAT_ARGS_HPP
