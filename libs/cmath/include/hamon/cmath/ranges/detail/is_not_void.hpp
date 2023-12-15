/**
 *	@file	is_not_void.hpp
 *
 *	@brief	is_not_void の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_IS_NOT_VOID_HPP
#define HAMON_CMATH_RANGES_DETAIL_IS_NOT_VOID_HPP

#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/negation.hpp>

namespace hamon
{
namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept is_not_void = !hamon::is_void<T>::value;

#else

template <typename T>
using is_not_void = hamon::negation<hamon::is_void<T>>;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_IS_NOT_VOID_HPP
