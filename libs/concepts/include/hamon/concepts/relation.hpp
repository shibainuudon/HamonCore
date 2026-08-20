/**
 *	@file	relation.hpp
 *
 *	@brief	relation の定義
 */

#ifndef HAMON_CONCEPTS_RELATION_HPP
#define HAMON_CONCEPTS_RELATION_HPP

#include <hamon/concepts/predicate.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.5 Concept relation	[concept.relation]

template <typename Rel, typename T, typename U>
HAMON_CONCEPT_OR_BOOL relation =
	hamon::predicate<Rel, T, T> &&
	hamon::predicate<Rel, U, U> &&
	hamon::predicate<Rel, T, U> &&
	hamon::predicate<Rel, U, T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_RELATION_HPP
