/**
 *	@file	destructible.hpp
 *
 *	@brief	destructible の定義
 */

#ifndef HAMON_CONCEPTS_DESTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DESTRUCTIBLE_HPP

#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.10 Concept destructible	[concept.destructible]

template <typename T>
HAMON_CONCEPT_OR_BOOL destructible = hamon::is_nothrow_destructible<T>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_DESTRUCTIBLE_HPP
