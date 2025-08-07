/**
 *	@file	__unpacked_format_arg_store.hpp
 *
 *	@brief	__unpacked_format_arg_store の定義
 */

#ifndef HAMON_FORMAT___FORMAT___UNPACKED_FORMAT_ARG_STORE_HPP
#define HAMON_FORMAT___FORMAT___UNPACKED_FORMAT_ARG_STORE_HPP

#include <hamon/format/basic_format_arg.hpp>

namespace hamon
{

namespace __format
{

template <class _Context, size_t _Np>
struct __unpacked_format_arg_store
{
	hamon::basic_format_arg<_Context> __args_[_Np];
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___UNPACKED_FORMAT_ARG_STORE_HPP
