/**
 *	@file	destroy_at.hpp
 *
 *	@brief	ranges::destroy_at を定義
 */

#ifndef HAMON_MEMORY_RANGES_DESTROY_AT_HPP
#define HAMON_MEMORY_RANGES_DESTROY_AT_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::destroy_at;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/destructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/memory/destroy_at.hpp>

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
	template <HAMON_CONSTRAINED_PARAM(hamon::destructible, T)>
	HAMON_CXX14_CONSTEXPR void operator()(T* location) const noexcept
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

#endif

#endif // HAMON_MEMORY_RANGES_DESTROY_AT_HPP
