/**
 *	@file	construct_at.hpp
 *
 *	@brief	ranges::construct_at を定義
 */

#ifndef HAMON_MEMORY_RANGES_CONSTRUCT_AT_HPP
#define HAMON_MEMORY_RANGES_CONSTRUCT_AT_HPP

#include <hamon/memory/construct_at.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 26.11.8 construct_at[specialized.construct]

struct construct_at_fn
{
public:
	template <typename T, typename... Args>
	//requires requires(T* location, Args&&... args) {
	//	::new (static_cast<void*>(location)) T(static_cast<Args&&>(args)...); // [specialized.construct]/1
	//}
	constexpr auto operator()(T* location, Args&&... args) const
		noexcept(noexcept(hamon::construct_at(location, hamon::forward<Args>(args)...)))
		->decltype(hamon::construct_at(location, hamon::forward<Args>(args)...))
	{
		return hamon::construct_at(location, hamon::forward<Args>(args)...);
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::construct_at_fn construct_at{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_CONSTRUCT_AT_HPP
