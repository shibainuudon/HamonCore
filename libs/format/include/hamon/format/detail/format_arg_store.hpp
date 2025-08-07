/**
 *	@file	format_arg_store.hpp
 *
 *	@brief	format_arg_store の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FORMAT_ARG_STORE_HPP
#define HAMON_FORMAT_DETAIL_FORMAT_ARG_STORE_HPP

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/array.hpp>


#include <hamon/format/__format/__use_packed_format_arg_store.hpp>
#include <hamon/format/__format/__create_packed_storage.hpp>
#include <hamon/format/__format/__store_basic_format_arg.hpp>
#include <hamon/format/__format/__packed_format_arg_store.hpp>
#include <hamon/format/__format/__unpacked_format_arg_store.hpp>
#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

namespace detail
{

#if 0

// 28.5.8.2 Class template format-arg-store[format.arg.store]

template <typename Context, typename... Args>
class format_arg_store
{
public:
	// TODO
	format_arg_store(Args&... __args) noexcept
		: args{hamon::basic_format_arg<Context>(__args)...}
	{}

	hamon::array<hamon::basic_format_arg<Context>, sizeof...(Args)> args;
};

#endif

template <class _Context, class... _Args>
struct format_arg_store
{
	format_arg_store(_Args&... __args) noexcept
	{
		if constexpr (sizeof...(_Args) != 0)
		{
			if constexpr (__format::__use_packed_format_arg_store(sizeof...(_Args)))
			{
				__format::__create_packed_storage(__storage.__types_, __storage.__values_, __args...);
			}
			else
			{
				__format::__store_basic_format_arg<_Context>(__storage.__args_, __args...);
			}
		}
	}

	using _Storage =
		hamon::conditional_t<__format::__use_packed_format_arg_store(sizeof...(_Args)),
		__format::__packed_format_arg_store<_Context, sizeof...(_Args)>,
		__format::__unpacked_format_arg_store<_Context, sizeof...(_Args)>>;

	_Storage __storage;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FORMAT_ARG_STORE_HPP
