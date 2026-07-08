/**
 *	@file	copy_constructible.hpp
 *
 *	@brief	copy_constructible の定義
 */

#ifndef HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#endif

namespace hamon
{

// 18.4.14 Concept copy_constructible	[concept.copyconstructible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::copy_constructible;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL copy_constructible =
	hamon::move_constructible<T> &&
	hamon::constructible_from<T, hamon::add_lvalue_reference_t<T>> &&
	hamon::constructible_from<T, hamon::add_lvalue_reference_t<hamon::add_const_t<T>>> &&
	hamon::constructible_from<T, hamon::add_const_t<T>> &&
	hamon::convertible_to<hamon::add_lvalue_reference_t<T>, T> &&
	hamon::convertible_to<hamon::add_lvalue_reference_t<hamon::add_const_t<T>>, T> &&
	hamon::convertible_to<hamon::add_const_t<T>, T>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
