/**
 *	@file	equality_comparable.hpp
 *
 *	@brief	equality_comparable の定義
 */

#ifndef HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP
#define HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#endif

namespace hamon
{

// 18.5.4 Concept equality_comparable	[concept.equalitycomparable]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::equality_comparable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept equality_comparable = detail::weakly_equality_comparable_with<T, T>;

#else

template <typename T>
using equality_comparable = detail::weakly_equality_comparable_with<T, T>;

#endif

template <typename T>
using equality_comparable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::equality_comparable<T>>;
#else
	hamon::equality_comparable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP
