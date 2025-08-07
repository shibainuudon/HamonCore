/**
 *	@file	__float_buffer_size.hpp
 *
 *	@brief	__float_buffer_size の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FLOAT_BUFFER_SIZE_HPP
#define HAMON_FORMAT___FORMATTER___FLOAT_BUFFER_SIZE_HPP

#include <hamon/format/__formatter/__traits.hpp>
#include <hamon/concepts/floating_point.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

template <hamon::floating_point _Fp>
constexpr size_t __float_buffer_size(int __precision)
{
	using _Traits = __formatter::__traits<_Fp>;
	return 4 + _Traits::__max_integral + __precision + _Traits::__max_fractional_value;
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FLOAT_BUFFER_SIZE_HPP
