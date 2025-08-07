/**
 *	@file	basic_format_args.hpp
 *
 *	@brief	basic_format_args の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP
#define HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_args;

}	// namespace hamon

#else

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/detail/format_arg_store.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

template <typename Context>
class basic_format_args
{
	hamon::size_t size_;                               // exposition only
	const hamon::basic_format_arg<Context>* data_;     // exposition only

public:
	template <typename... Args>
	basic_format_args(hamon::detail::format_arg_store<Context, Args...> const& store) noexcept;

	hamon::basic_format_arg<Context> get(hamon::size_t i) const noexcept;
};

template <typename Context, typename... Args>
basic_format_args(hamon::detail::format_arg_store<Context, Args...>)
	->basic_format_args<Context>;

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_ARGS_HPP
