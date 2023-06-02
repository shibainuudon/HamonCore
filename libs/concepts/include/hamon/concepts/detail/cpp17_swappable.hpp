/**
 *	@file	cpp17_swappable.hpp
 *
 *	@brief	cpp17_swappable の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_SWAPPABLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_SWAPPABLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cpp17_swappable = hamon::is_swappable_v<T>;

#else

template <typename T>
using cpp17_swappable = hamon::is_swappable<T>;

#endif

template <typename T>
using cpp17_swappable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_swappable<T>>;
#else
	hamon::detail::cpp17_swappable<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_SWAPPABLE_HPP
