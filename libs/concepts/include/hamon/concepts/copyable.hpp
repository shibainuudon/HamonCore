/**
 *	@file	copyable.hpp
 *
 *	@brief	copyable の定義
 */

#ifndef HAMON_CONCEPTS_COPYABLE_HPP
#define HAMON_CONCEPTS_COPYABLE_HPP

#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.6 Object concepts	[concepts.object]

template <typename T>
HAMON_CONCEPT_OR_BOOL copyable =
	hamon::copy_constructible<T> &&
	hamon::movable<T> &&
	hamon::assignable_from<hamon::add_lvalue_reference_t<T>, hamon::add_lvalue_reference_t<T>> &&
	hamon::assignable_from<hamon::add_lvalue_reference_t<T>, hamon::add_lvalue_reference_t<hamon::add_const_t<T>>> &&
	hamon::assignable_from<hamon::add_lvalue_reference_t<T>, hamon::add_const_t<T>>;

// not_copyable
template <typename T>
HAMON_CONCEPT_OR_BOOL not_copyable = !hamon::copyable<T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_COPYABLE_HPP
