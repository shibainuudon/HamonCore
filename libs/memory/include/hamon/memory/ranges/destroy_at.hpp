/**
 *	@file	destroy_at.hpp
 *
 *	@brief	ranges::destroy_at を定義
 */

#ifndef HAMON_MEMORY_RANGES_DESTROY_AT_HPP
#define HAMON_MEMORY_RANGES_DESTROY_AT_HPP

#include <hamon/concepts/destructible.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.9 destroy[specialized.destroy]

struct destroy_at_fn
{
public:
	template <HAMON_CONSTRAINT(hamon::destructible, T)>
	HAMON_CXX14_CONSTEXPR void
	operator()(T* location) const HAMON_NOEXCEPT
	{
		hamon::destroy_at(location);
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::destroy_at_fn destroy_at{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DESTROY_AT_HPP
