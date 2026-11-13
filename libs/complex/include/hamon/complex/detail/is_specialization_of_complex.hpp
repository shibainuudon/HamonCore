/**
 *	@file	is_specialization_of_complex.hpp
 *
 *	@brief	is_specialization_of_complex の定義
 */

#ifndef HAMON_COMPLEX_DETAIL_IS_SPECIALIZATION_OF_COMPLEX_HPP
#define HAMON_COMPLEX_DETAIL_IS_SPECIALIZATION_OF_COMPLEX_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <complex>
#endif

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_complex
	: public hamon::false_type {};

#if !defined(HAMON_NO_STD)
template <typename T>
struct is_specialization_of_complex<std::complex<T>>
	: public hamon::true_type {};
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPLEX_DETAIL_IS_SPECIALIZATION_OF_COMPLEX_HPP
