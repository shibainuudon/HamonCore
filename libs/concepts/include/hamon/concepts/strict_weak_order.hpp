/**
 *	@file	strict_weak_order.hpp
 *
 *	@brief	strict_weak_order の定義
 */

#ifndef HAMON_CONCEPTS_STRICT_WEAK_ORDER_HPP
#define HAMON_CONCEPTS_STRICT_WEAK_ORDER_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/relation.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.7 Concept strict_weak_order	[concept.strictweakorder]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::strict_weak_order;

#else

template <typename Rel, typename T, typename U>
HAMON_CONCEPT_OR_BOOL strict_weak_order = hamon::relation<Rel, T, U>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_STRICT_WEAK_ORDER_HPP
