/**
 *	@file	__number_max.hpp
 *
 *	@brief	__number_max の定義
 */

#ifndef HAMON_FORMAT___FORMAT___NUMBER_MAX_HPP
#define HAMON_FORMAT___FORMAT___NUMBER_MAX_HPP


namespace hamon
{

namespace __format
{

/**
 * The maximum value of a numeric argument.
 *
 * This is used for:
 * * arg-id
 * * width as value or arg-id.
 * * precision as value or arg-id.
 *
 * The value is compatible with the maximum formatting width and precision
 * using the `%*` syntax on a 32-bit system.
 */
inline constexpr uint32_t __number_max = INT32_MAX;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___NUMBER_MAX_HPP
