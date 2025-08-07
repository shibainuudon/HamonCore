/**
 *	@file	__fields_range.hpp
 *
 *	@brief	__fields_range の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___FIELDS_RANGE_HPP
#define HAMON_FORMAT___FORMAT_SPEC___FIELDS_RANGE_HPP

#include <hamon/format/__format_spec/__fields.hpp>

namespace hamon
{

namespace __format_spec
{

inline constexpr __format_spec::__fields
__fields_range
{
	.__use_range_fill_ = true,
	.__clear_brackets_ = true
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___FIELDS_RANGE_HPP
