/**
 *	@file	regular_invocable.hpp
 *
 *	@brief	regular_invocable の定義
 */

#ifndef HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP
#define HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP

#include <hamon/concepts/invocable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.3 Concept regular_invocable	[concept.regularinvocable]

template <typename Fn, typename... Args>
HAMON_CONCEPT_OR_BOOL regular_invocable = hamon::invocable<Fn, Args...>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP
