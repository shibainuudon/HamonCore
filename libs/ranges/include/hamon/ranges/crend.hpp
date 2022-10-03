/**
 *	@file	crend.hpp
 *
 *	@brief	ranges::crend の定義
 */

#ifndef HAMON_RANGES_CREND_HPP
#define HAMON_RANGES_CREND_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/iterator/reverse_iterator.hpp>

#if defined(HAMON_USE_STD_RANGES) && defined(HAMON_USE_STD_REVERSE_ITERATOR)

namespace hamon {
namespace ranges {

using std::ranges::crend;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/rend.hpp>
#include <hamon/ranges/detail/as_const.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct crend_fn
{
	template <typename T>
	constexpr auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			ranges::rend(ranges::detail::as_const(std::forward<T>(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::crend_fn crend{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_CREND_HPP
