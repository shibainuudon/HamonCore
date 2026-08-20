/**
 *	@file	move_constructible.hpp
 *
 *	@brief	move_constructible の定義
 */

#ifndef HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP

#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.13 Concept move_constructible	[concept.moveconstructible]

template <typename T>
HAMON_CONCEPT_OR_BOOL move_constructible =
	hamon::constructible_from<T, T> &&
	hamon::convertible_to<T, T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
