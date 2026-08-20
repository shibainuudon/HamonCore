/**
 *	@file	floating_point.hpp
 *
 *	@brief	floating_point の定義
 */

#ifndef HAMON_CONCEPTS_FLOATING_POINT_HPP
#define HAMON_CONCEPTS_FLOATING_POINT_HPP

#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

template <typename T>
HAMON_CONCEPT_OR_BOOL floating_point = hamon::is_floating_point<T>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_FLOATING_POINT_HPP
