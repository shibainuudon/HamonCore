/**
 *	@file	__fields_string.hpp
 *
 *	@brief	__fields_string の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___FIELDS_STRING_HPP
#define HAMON_FORMAT___FORMAT_SPEC___FIELDS_STRING_HPP

#include <hamon/format/__format_spec/__fields.hpp>

namespace hamon
{

namespace __format_spec
{

inline constexpr __format_spec::__fields
__fields_string
{
	.__precision_   = true,
	.__type_        = true,
	.__consume_all_ = true
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___FIELDS_STRING_HPP
