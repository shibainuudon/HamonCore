/**
 *	@file	move_constructible.hpp
 *
 *	@brief	move_constructible の定義
 */

#ifndef HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.13 Concept move_constructible	[concept.moveconstructible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::move_constructible;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL move_constructible =
	hamon::constructible_from<T, T> &&
	hamon::convertible_to<T, T>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
