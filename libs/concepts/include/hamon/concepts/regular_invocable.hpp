/**
 *	@file	regular_invocable.hpp
 *
 *	@brief	regular_invocable の定義
 */

#ifndef HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP
#define HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/invocable.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.3 Concept regular_invocable	[concept.regularinvocable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::regular_invocable;

#else

template <typename Fn, typename... Args>
HAMON_CONCEPT_OR_BOOL regular_invocable = hamon::invocable<Fn, Args...>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_REGULAR_INVOCABLE_HPP
