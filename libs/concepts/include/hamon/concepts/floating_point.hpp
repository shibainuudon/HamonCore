/**
 *	@file	floating_point.hpp
 *
 *	@brief	floating_point の定義
 */

#ifndef HAMON_CONCEPTS_FLOATING_POINT_HPP
#define HAMON_CONCEPTS_FLOATING_POINT_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_floating_point.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::floating_point;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept floating_point = hamon::is_floating_point<T>::value;

#else

template <typename T>
using floating_point = hamon::is_floating_point<T>;

#endif

template <typename T>
using floating_point_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::floating_point<T>>;
#else
	hamon::floating_point<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_FLOATING_POINT_HPP
