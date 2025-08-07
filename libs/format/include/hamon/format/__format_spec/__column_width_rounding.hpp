/**
 *	@file	__column_width_rounding.hpp
 *
 *	@brief	__column_width_rounding の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___COLUMN_WIDTH_ROUNDING_HPP
#define HAMON_FORMAT___FORMAT_SPEC___COLUMN_WIDTH_ROUNDING_HPP

namespace hamon
{

namespace __format_spec
{

/// Since a column width can be two it's possible that the requested column
/// width can't be achieved. Depending on the intended usage the policy can be
/// selected.
/// - When used as precision the maximum width may not be exceeded and the
///   result should be "rounded down" to the previous boundary.
/// - When used as a width we're done once the minimum is reached, but
///   exceeding is not an issue. Rounding down is an issue since that will
///   result in writing fill characters. Therefore the result needs to be
///   "rounded up".
enum class __column_width_rounding { __down, __up };

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___COLUMN_WIDTH_ROUNDING_HPP
