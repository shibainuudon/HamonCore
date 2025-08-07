/**
 *	@file	make_format_args.hpp
 *
 *	@brief	make_format_args の定義
 */

#ifndef HAMON_FORMAT_MAKE_FORMAT_ARGS_HPP
#define HAMON_FORMAT_MAKE_FORMAT_ARGS_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::make_format_args;

}	// namespace hamon

#else

#include <hamon/format/format_context.hpp>
#include <hamon/format/detail/format_arg_store.hpp>

namespace hamon
{

// 28.5.8.2 Class template format-arg-store[format.arg.store]

template <typename Context = hamon::format_context, typename... Args>
hamon::detail::format_arg_store<Context, Args...>
make_format_args(Args&... fmt_args)
{
	// TODO
	// [format.arg.store]/2
	// Preconditions: The type typename Context​::​template formatter_type<remove_const_t<Ti>>
	// meets the BasicFormatter requirements ([formatter.requirements]) for each Ti in Args.

	// [format.arg.store]/3
	return hamon::detail::format_arg_store<Context, Args...>(fmt_args...);
}

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_MAKE_FORMAT_ARGS_HPP
