/**
 *	@file	invocable.hpp
 *
 *	@brief	invocable の定義
 */

#ifndef HAMON_CONCEPTS_INVOCABLE_HPP
#define HAMON_CONCEPTS_INVOCABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_invocable.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.2 Concept invocable	[concept.invocable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::invocable;

#else

template <typename Fn, typename... Args>
HAMON_CONCEPT_OR_BOOL invocable = hamon::is_invocable<Fn, Args...>::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_INVOCABLE_HPP
