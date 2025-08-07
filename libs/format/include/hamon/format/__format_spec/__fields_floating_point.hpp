/**
 *	@file	__fields_floating_point.hpp
 *
 *	@brief	__fields_floating_point の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___FIELDS_FLOATING_POINT_HPP
#define HAMON_FORMAT___FORMAT_SPEC___FIELDS_FLOATING_POINT_HPP

#include <hamon/format/__format_spec/__fields.hpp>

namespace hamon
{

namespace __format_spec
{

inline constexpr __format_spec::__fields
__fields_floating_point
{
    .__sign_                 = true,
    .__alternate_form_       = true,
    .__zero_padding_         = true,
    .__precision_            = true,
    .__locale_specific_form_ = true,
    .__type_                 = true,
    .__consume_all_          = true
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___FIELDS_FLOATING_POINT_HPP
