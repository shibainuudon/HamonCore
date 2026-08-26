/**
 *	@file	default_sentinel_t.hpp
 *
 *	@brief	default_sentinel_t の定義
 */

#ifndef HAMON_ITERATOR_DEFAULT_SENTINEL_T_HPP
#define HAMON_ITERATOR_DEFAULT_SENTINEL_T_HPP

#include <hamon/config.hpp>

namespace hamon
{

struct default_sentinel_t {};

HAMON_INLINE_VAR HAMON_CONSTEXPR
default_sentinel_t default_sentinel{};

}	// namespace hamon

#endif // HAMON_ITERATOR_DEFAULT_SENTINEL_T_HPP
