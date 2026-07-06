/**
 *	@file	constructible_from.hpp
 *
 *	@brief	constructible_from の定義
 */

#ifndef HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/destructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.11 Concept constructible_from	[concept.constructible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::constructible_from;

#else

template <typename T, typename... Args>
HAMON_CONCEPT_OR_BOOL constructible_from =
	hamon::destructible<T> &&
	hamon::is_constructible<T, Args...>::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
