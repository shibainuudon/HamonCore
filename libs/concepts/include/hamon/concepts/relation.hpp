/**
 *	@file	relation.hpp
 *
 *	@brief	relation の定義
 */

#ifndef HAMON_CONCEPTS_RELATION_HPP
#define HAMON_CONCEPTS_RELATION_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/predicate.hpp>
#include <hamon/type_traits/conjunction.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::relation;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Rel, typename T, typename U>
concept relation =
	hamon::predicate<Rel, T, T> &&
	hamon::predicate<Rel, U, U> &&
	hamon::predicate<Rel, T, U> &&
	hamon::predicate<Rel, U, T>;

#else

template <typename Rel, typename T, typename U>
using relation =
	hamon::conjunction<
		hamon::predicate<Rel, T, T>,
		hamon::predicate<Rel, U, U>,
		hamon::predicate<Rel, T, U>,
		hamon::predicate<Rel, U, T>
	>;

#endif

}	// namespace hamon

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Rel, typename T, typename U>
using relation_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::relation<Rel, T, U>>;
#else
	hamon::relation<Rel, T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_RELATION_HPP
