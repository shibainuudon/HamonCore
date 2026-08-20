/**
 *	@file	totally_ordered.hpp
 *
 *	@brief	totally_ordered の定義
 */

#ifndef HAMON_CONCEPTS_TOTALLY_ORDERED_HPP
#define HAMON_CONCEPTS_TOTALLY_ORDERED_HPP

#include <hamon/compare/detail/partially_ordered_with.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.5.5 Concept totally_ordered	[concept.totallyordered]

template <typename T>
HAMON_CONCEPT_OR_BOOL totally_ordered =
	hamon::equality_comparable<T> &&
	detail::partially_ordered_with<T, T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_TOTALLY_ORDERED_HPP
