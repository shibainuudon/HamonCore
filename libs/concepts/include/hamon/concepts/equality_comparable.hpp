/**
 *	@file	equality_comparable.hpp
 *
 *	@brief	equality_comparable の定義
 */

#ifndef HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP
#define HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.5.4 Concept equality_comparable	[concept.equalitycomparable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::equality_comparable;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL equality_comparable = detail::weakly_equality_comparable_with<T, T>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP
