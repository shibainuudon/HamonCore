/**
 *	@file	default_sentinel.hpp
 *
 *	@brief	default_sentinel の定義
 */

#ifndef HAMON_ITERATOR_DEFAULT_SENTINEL_HPP
#define HAMON_ITERATOR_DEFAULT_SENTINEL_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::default_sentinel_t;
using std::default_sentinel;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

struct default_sentinel_t {};

HAMON_INLINE_VAR HAMON_CONSTEXPR
default_sentinel_t default_sentinel{};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_DEFAULT_SENTINEL_HPP
