/**
 *	@file	__packed_types_max.hpp
 *
 *	@brief	__packed_types_max の定義
 */

#ifndef HAMON_FORMAT___FORMAT___PACKED_TYPES_MAX_HPP
#define HAMON_FORMAT___FORMAT___PACKED_TYPES_MAX_HPP

#include <hamon/format/__format/__packed_types_storage_bits.hpp>
#include <hamon/format/__format/__packed_arg_t_bits.hpp>

namespace hamon
{

namespace __format
{

inline constexpr unsigned __packed_types_max = __format::__packed_types_storage_bits / __format::__packed_arg_t_bits;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___PACKED_TYPES_MAX_HPP
