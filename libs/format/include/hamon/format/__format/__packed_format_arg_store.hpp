/**
 *	@file	__packed_format_arg_store.hpp
 *
 *	@brief	__packed_format_arg_store の定義
 */

#ifndef HAMON_FORMAT___FORMAT___PACKED_FORMAT_ARG_STORE_HPP
#define HAMON_FORMAT___FORMAT___PACKED_FORMAT_ARG_STORE_HPP

#include <hamon/format/detail/__basic_format_arg_value.hpp>

namespace hamon
{

namespace __format
{

template <class _Context, size_t _Np>
struct __packed_format_arg_store
{
	hamon::detail::__basic_format_arg_value<_Context> __values_[_Np];
	uint64_t __types_ = 0;
};

template <class _Context>
struct __packed_format_arg_store<_Context, 0>
{
	uint64_t __types_ = 0;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___PACKED_FORMAT_ARG_STORE_HPP
