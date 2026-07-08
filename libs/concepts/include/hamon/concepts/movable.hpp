/**
 *	@file	movable.hpp
 *
 *	@brief	movable の定義
 */

#ifndef HAMON_CONCEPTS_MOVABLE_HPP
#define HAMON_CONCEPTS_MOVABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/swappable.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/is_object.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.6 Object concepts	[concepts.object]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::movable;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL movable =
	hamon::is_object<T>::value &&
	hamon::move_constructible<T> &&
	hamon::assignable_from<hamon::add_lvalue_reference_t<T>, T> &&
	hamon::swappable<T>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_MOVABLE_HPP
