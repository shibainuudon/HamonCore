/**
 *	@file	equivalence_relation.hpp
 *
 *	@brief	equivalence_relation の定義
 */

#ifndef HAMON_CONCEPTS_EQUIVALENCE_RELATION_HPP
#define HAMON_CONCEPTS_EQUIVALENCE_RELATION_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/relation.hpp>
#endif

namespace hamon
{

// 18.7.6 Concept equivalence_relation	[concept.equiv]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::equivalence_relation;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Rel, typename T, typename U>
concept equivalence_relation = hamon::relation<Rel, T, U>;

#else

template <typename Rel, typename T, typename U>
using equivalence_relation = hamon::relation<Rel, T, U>;

#endif

template <typename Rel, typename T, typename U>
using equivalence_relation_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::equivalence_relation<Rel, T, U>>;
#else
	hamon::equivalence_relation<Rel, T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUIVALENCE_RELATION_HPP
