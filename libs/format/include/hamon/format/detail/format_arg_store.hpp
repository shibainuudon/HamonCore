/**
 *	@file	format_arg_store.hpp
 *
 *	@brief	format_arg_store の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FORMAT_ARG_STORE_HPP
#define HAMON_FORMAT_DETAIL_FORMAT_ARG_STORE_HPP

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/array.hpp>

namespace hamon
{

namespace detail
{

// 28.5.8.2 Class template format-arg-store[format.arg.store]

template <typename Context, typename... Args>
class format_arg_store
{
public:
	format_arg_store(Args&... __args) noexcept
		: args{hamon::basic_format_arg<Context>(__args)... }
	{}

	hamon::array<hamon::basic_format_arg<Context>, sizeof...(Args)> args;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FORMAT_ARG_STORE_HPP
