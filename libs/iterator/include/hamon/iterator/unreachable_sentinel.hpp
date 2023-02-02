/**
 *	@file	unreachable_sentinel.hpp
 *
 *	@brief	unreachable_sentinel の定義
 */

#ifndef HAMON_ITERATOR_UNREACHABLE_SENTINEL_HPP
#define HAMON_ITERATOR_UNREACHABLE_SENTINEL_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::unreachable_sentinel_t;
using std::unreachable_sentinel;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

struct unreachable_sentinel_t
{
	template <HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, It)>
	friend HAMON_CONSTEXPR bool
	operator==(unreachable_sentinel_t, It const&) HAMON_NOEXCEPT
	{
		return false;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, It)>
	friend HAMON_CONSTEXPR bool
	operator!=(unreachable_sentinel_t, It const&) HAMON_NOEXCEPT
	{
		return true;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, It)>
	friend HAMON_CONSTEXPR bool
	operator==(It const&, unreachable_sentinel_t) HAMON_NOEXCEPT
	{
		return false;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, It)>
	friend HAMON_CONSTEXPR bool
	operator!=(It const&, unreachable_sentinel_t) HAMON_NOEXCEPT
	{
		return true;
	}
};

HAMON_INLINE_VAR HAMON_CONSTEXPR
unreachable_sentinel_t unreachable_sentinel{};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_UNREACHABLE_SENTINEL_HPP
