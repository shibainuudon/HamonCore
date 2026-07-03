/**
 *	@file	integral.hpp
 *
 *	@brief	integral の定義
 */

#ifndef HAMON_CONCEPTS_INTEGRAL_HPP
#define HAMON_CONCEPTS_INTEGRAL_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_integral.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::integral;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL integral = hamon::is_integral<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_INTEGRAL_HPP
