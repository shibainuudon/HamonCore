/**
 *	@file	disable_sized_sentinel_for.hpp
 *
 *	@brief	disable_sized_sentinel_for の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP

#include <hamon/config.hpp>

namespace hamon
{

template <typename Sent, typename Iter>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool disable_sized_sentinel_for = false;

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
