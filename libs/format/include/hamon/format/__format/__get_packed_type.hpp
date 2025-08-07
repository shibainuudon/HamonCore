/**
 *	@file	__get_packed_type.hpp
 *
 *	@brief	__get_packed_type の定義
 */

#ifndef HAMON_FORMAT___FORMAT___GET_PACKED_TYPE_HPP
#define HAMON_FORMAT___FORMAT___GET_PACKED_TYPE_HPP

#include <hamon/format/__format/__arg_t.hpp>
#include <hamon/format/__format/__packed_types_max.hpp>
#include <hamon/format/__format/__packed_arg_t_bits.hpp>
#include <hamon/format/__format/__packed_arg_t_mask.hpp>

namespace hamon
{

namespace __format
{

constexpr __format::__arg_t __get_packed_type(uint64_t __types, size_t __id)
{
//	_LIBCPP_ASSERT_INTERNAL(__id <= __format::__packed_types_max, "");

	if (__id > 0)
	{
		__types >>= __id * __format::__packed_arg_t_bits;
	}

	return static_cast<__format::__arg_t>(__types & __format::__packed_arg_t_mask);
}

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___GET_PACKED_TYPE_HPP
