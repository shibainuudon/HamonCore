/**
 *	@file	arithmetic.hpp
 *
 *	@brief	arithmetic の定義
 */

#ifndef HAMON_CONCEPTS_ARITHMETIC_HPP
#define HAMON_CONCEPTS_ARITHMETIC_HPP

#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
HAMON_CONCEPT_OR_BOOL arithmetic = hamon::is_arithmetic<T>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_ARITHMETIC_HPP
