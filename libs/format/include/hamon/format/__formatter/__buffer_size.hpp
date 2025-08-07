/**
 *	@file	__buffer_size.hpp
 *
 *	@brief	__buffer_size の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___BUFFER_SIZE_HPP
#define HAMON_FORMAT___FORMATTER___BUFFER_SIZE_HPP

#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/limits.hpp>

namespace hamon
{

namespace __formatter
{

/**
 * Helper to determine the buffer size to output a integer in Base @em x.
 *
 * There are several overloads for the supported bases. The function uses the
 * base as template argument so it can be used in a constant expression.
 */
template <hamon::unsigned_integral _Tp, size_t _Base>
consteval size_t __buffer_size() noexcept
requires(_Base == 2)
{
	return hamon::numeric_limits<_Tp>::digits // The number of binary digits.
		+ 2                           // Reserve space for the '0[Bb]' prefix.
		+ 1;                          // Reserve space for the sign.
}

template <hamon::unsigned_integral _Tp, size_t _Base>
consteval size_t __buffer_size() noexcept
requires(_Base == 8)
{
	return hamon::numeric_limits<_Tp>::digits // The number of binary digits.
		/ 3                       // Adjust to octal.
		+ 1                           // Turn floor to ceil.
		+ 1                           // Reserve space for the '0' prefix.
		+ 1;                          // Reserve space for the sign.
}

template <hamon::unsigned_integral _Tp, size_t _Base>
consteval size_t __buffer_size() noexcept
requires(_Base == 10)
{
	return hamon::numeric_limits<_Tp>::digits10 // The floored value.
		+ 1                             // Turn floor to ceil.
		+ 1;                            // Reserve space for the sign.
}

template <hamon::unsigned_integral _Tp, size_t _Base>
consteval size_t __buffer_size() noexcept
requires(_Base == 16)
{
	return hamon::numeric_limits<_Tp>::digits // The number of binary digits.
		/ 4                       // Adjust to hexadecimal.
		+ 2                           // Reserve space for the '0[Xx]' prefix.
		+ 1;                          // Reserve space for the sign.
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___BUFFER_SIZE_HPP
