/**
 *	@file	destructible.hpp
 *
 *	@brief	destructible の定義
 */

#ifndef HAMON_CONCEPTS_DESTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DESTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.10 Concept destructible	[concept.destructible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::destructible;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL destructible = hamon::is_nothrow_destructible<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_DESTRUCTIBLE_HPP
