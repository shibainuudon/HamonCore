/**
 *	@file	equivalence_relation.hpp
 *
 *	@brief	equivalence_relation の定義
 */

#ifndef HAMON_CONCEPTS_EQUIVALENCE_RELATION_HPP
#define HAMON_CONCEPTS_EQUIVALENCE_RELATION_HPP

#include <hamon/concepts/relation.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.6 Concept equivalence_relation	[concept.equiv]

template <typename Rel, typename T, typename U>
HAMON_CONCEPT_OR_BOOL equivalence_relation = hamon::relation<Rel, T, U>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUIVALENCE_RELATION_HPP
