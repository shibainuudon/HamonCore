/**
 *	@file	constructible_from.hpp
 *
 *	@brief	constructible_from の定義
 */

#ifndef HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include <hamon/concepts/destructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.11 Concept constructible_from	[concept.constructible]

template <typename T, typename... Args>
HAMON_CONCEPT_OR_BOOL constructible_from =
	hamon::destructible<T> &&
	hamon::is_constructible<T, Args...>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
