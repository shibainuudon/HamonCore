/**
 *	@file	integral.hpp
 *
 *	@brief	integral の定義
 */

#ifndef HAMON_CONCEPTS_INTEGRAL_HPP
#define HAMON_CONCEPTS_INTEGRAL_HPP

#include <hamon/type_traits/is_integral.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

template <typename T>
HAMON_CONCEPT_OR_BOOL integral = hamon::is_integral<T>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_INTEGRAL_HPP
