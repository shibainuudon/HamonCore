/**
 *	@file	arithmetic.hpp
 *
 *	@brief	arithmetic の定義
 */

#ifndef HAMON_CONCEPTS_ARITHMETIC_HPP
#define HAMON_CONCEPTS_ARITHMETIC_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept arithmetic = hamon::is_arithmetic<T>::value;

#else

template <typename T>
using arithmetic = hamon::is_arithmetic<T>;

#endif

template <typename T>
using arithmetic_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::arithmetic<T>>;
#else
	hamon::arithmetic<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_ARITHMETIC_HPP
