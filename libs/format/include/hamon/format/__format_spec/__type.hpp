/**
 *	@file	__type.hpp
 *
 *	@brief	__type の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___TYPE_HPP
#define HAMON_FORMAT___FORMAT_SPEC___TYPE_HPP


namespace hamon
{

namespace __format_spec
{

enum class __type : uint8_t
{
	__default = 0,
	__string,
	__binary_lower_case,
	__binary_upper_case,
	__octal,
	__decimal,
	__hexadecimal_lower_case,
	__hexadecimal_upper_case,
	__pointer_lower_case,
	__pointer_upper_case,
	__char,
	__hexfloat_lower_case,
	__hexfloat_upper_case,
	__scientific_lower_case,
	__scientific_upper_case,
	__fixed_lower_case,
	__fixed_upper_case,
	__general_lower_case,
	__general_upper_case,
	__debug
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___TYPE_HPP
