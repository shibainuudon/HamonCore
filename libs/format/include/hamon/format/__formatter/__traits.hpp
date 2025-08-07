/**
 *	@file	__traits.hpp
 *
 *	@brief	__traits の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___TRAITS_HPP
#define HAMON_FORMAT___FORMATTER___TRAITS_HPP

namespace hamon
{

namespace __formatter
{

// TODO FMT Add long double specialization when to_chars has proper long double support.
template <class _Tp>
struct __traits;

template <>
struct __traits<float>
{
	static constexpr int __max_integral         = 38;
	static constexpr int __max_fractional       = 149;
	static constexpr int __max_fractional_value = 3;
	static constexpr size_t __stack_buffer_size = 256;

	static constexpr int __hex_precision_digits = 3;
};

template <>
struct __traits<double>
{
	static constexpr int __max_integral         = 308;
	static constexpr int __max_fractional       = 1074;
	static constexpr int __max_fractional_value = 4;
	static constexpr size_t __stack_buffer_size = 1024;

	static constexpr int __hex_precision_digits = 4;
};

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___TRAITS_HPP
