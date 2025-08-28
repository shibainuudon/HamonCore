/**
 *	@file	__format_floating_point_non_finite.hpp
 *
 *	@brief	__format_floating_point_non_finite の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FORMAT_FLOATING_POINT_NON_FINITE_HPP
#define HAMON_FORMAT___FORMATTER___FORMAT_FLOATING_POINT_NON_FINITE_HPP

#include <hamon/format/__format_spec/__parsed_specifications.hpp>
#include <hamon/format/__format_spec/__type.hpp>
#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__formatter/__insert_sign.hpp>
#include <hamon/format/__formatter/__write.hpp>
#include <hamon/algorithm/copy_n.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __formatter
{

template <class _OutIt, class _CharT>
_OutIt __format_floating_point_non_finite(
	_OutIt __out_it, __format_spec::__parsed_specifications<_CharT> __specs, bool __negative, bool __isnan)
{
	char __buffer[4];
	char* __last = __formatter::__insert_sign(__buffer, __negative, __specs.__std_.__sign_);

	// to_chars can return inf, infinity, nan, and nan(n-char-sequence).
	// The format library requires inf and nan.
	// All in one expression to avoid dangling references.
	bool __upper_case =
		__specs.__std_.__type_ == __format_spec::__type::__hexfloat_upper_case ||
		__specs.__std_.__type_ == __format_spec::__type::__scientific_upper_case ||
		__specs.__std_.__type_ == __format_spec::__type::__fixed_upper_case ||
		__specs.__std_.__type_ == __format_spec::__type::__general_upper_case;
	__last = hamon::copy_n(&("infnanINFNAN"[6 * __upper_case + 3 * __isnan]), 3, __last);

	// [format.string.std]/13
	// A zero (0) character preceding the width field pads the field with
	// leading zeros (following any indication of sign or base) to the field
	// width, except when applied to an infinity or NaN.
	if (__specs.__alignment_ == __format_spec::__alignment::__zero_padding)
	{
		__specs.__alignment_ = __format_spec::__alignment::__right;
	}

	return __formatter::__write(__buffer, __last, hamon::move(__out_it), __specs);
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FORMAT_FLOATING_POINT_NON_FINITE_HPP
