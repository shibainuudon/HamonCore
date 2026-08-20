/**
 *	@file	invocable.hpp
 *
 *	@brief	invocable の定義
 */

#ifndef HAMON_CONCEPTS_INVOCABLE_HPP
#define HAMON_CONCEPTS_INVOCABLE_HPP

#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.7.2 Concept invocable	[concept.invocable]

template <typename Fn, typename... Args>
HAMON_CONCEPT_OR_BOOL invocable = hamon::is_invocable<Fn, Args...>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_INVOCABLE_HPP
