/**
 *	@file	equality_comparable.hpp
 *
 *	@brief	equality_comparable の定義
 */

#ifndef HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP
#define HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::equality_comparable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept equality_comparable = detail::weakly_eq_cmp_with<T, T>;

#else

template <typename T>
using equality_comparable = detail::weakly_eq_cmp_with<T, T>;

#endif

}	// namespace hamon

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using equality_comparable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::equality_comparable<T>>;
#else
	hamon::equality_comparable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_EQUALITY_COMPARABLE_HPP
