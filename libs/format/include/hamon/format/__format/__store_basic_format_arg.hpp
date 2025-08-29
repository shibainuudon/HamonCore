/**
 *	@file	__store_basic_format_arg.hpp
 *
 *	@brief	__store_basic_format_arg の定義
 */

#ifndef HAMON_FORMAT___FORMAT___STORE_BASIC_FORMAT_ARG_HPP
#define HAMON_FORMAT___FORMAT___STORE_BASIC_FORMAT_ARG_HPP

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/__format/__create_format_arg.hpp>

namespace hamon
{

namespace __format
{

template <class _Context, class... _Args>
void __store_basic_format_arg(hamon::basic_format_arg<_Context>* __data, _Args&... __args) noexcept
{
	([&] { *__data++ = __format::__create_format_arg<_Context>(__args); }(), ...);
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___STORE_BASIC_FORMAT_ARG_HPP
