/**
 *	@file	is_not_void.hpp
 *
 *	@brief	is_not_void の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_IS_NOT_VOID_HPP
#define HAMON_CMATH_RANGES_DETAIL_IS_NOT_VOID_HPP

#include <hamon/type_traits/is_void.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
HAMON_CONCEPT_OR_BOOL is_not_void = !hamon::is_void<T>::value;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_IS_NOT_VOID_HPP
