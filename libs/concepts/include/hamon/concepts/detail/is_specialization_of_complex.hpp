/**
 *	@file	is_specialization_of_complex.hpp
 *
 *	@brief	is_specialization_of_complex の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_COMPLEX_HPP
#define HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_COMPLEX_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <complex>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_complex
	: public hamon::false_type {};

template <typename T>
struct is_specialization_of_complex<std::complex<T>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_COMPLEX_HPP
