/**
 *	@file	__use_packed_format_arg_store.hpp
 *
 *	@brief	__use_packed_format_arg_store の定義
 */

#ifndef HAMON_FORMAT___FORMAT___USE_PACKED_FORMAT_ARG_STORE_HPP
#define HAMON_FORMAT___FORMAT___USE_PACKED_FORMAT_ARG_STORE_HPP

#include <hamon/format/__format/__packed_types_max.hpp>

namespace hamon
{

namespace __format
{

constexpr bool __use_packed_format_arg_store(size_t __size)
{
	return __size <= __format::__packed_types_max;
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___USE_PACKED_FORMAT_ARG_STORE_HPP
