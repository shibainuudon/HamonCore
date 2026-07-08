/**
 *	@file	cpp17_swappable.hpp
 *
 *	@brief	cpp17_swappable の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_SWAPPABLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_SWAPPABLE_HPP

#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CONCEPT_OR_BOOL cpp17_swappable = hamon::is_swappable_v<T>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_SWAPPABLE_HPP
