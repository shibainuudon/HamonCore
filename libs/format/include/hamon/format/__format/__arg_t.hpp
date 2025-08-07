/**
 *	@file	__arg_t.hpp
 *
 *	@brief	__arg_t の定義
 */

#ifndef HAMON_FORMAT___FORMAT___ARG_T_HPP
#define HAMON_FORMAT___FORMAT___ARG_T_HPP

#include <hamon/cstdint.hpp>

namespace hamon
{

namespace __format
{

enum class __arg_t : hamon::uint8_t
{
	__none,
	__boolean,
	__char_type,
	__int,
	__long_long,
//	__i128, // extension
	__unsigned,
	__unsigned_long_long,
//	__u128, // extension
	__float,
	__double,
	__long_double,
	__const_char_type_ptr,
	__string_view,
	__ptr,
	__handle
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___ARG_T_HPP
