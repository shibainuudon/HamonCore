/**
 *	@file	floating_point.hpp
 *
 *	@brief	floating_point の定義
 */

#ifndef HAMON_CONCEPTS_FLOATING_POINT_HPP
#define HAMON_CONCEPTS_FLOATING_POINT_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_floating_point.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::floating_point;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL floating_point = hamon::is_floating_point<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_FLOATING_POINT_HPP
