﻿/**
 *	@file	crbegin.hpp
 *
 *	@brief	ranges::crbegin の定義
 */

#ifndef HAMON_RANGES_CRBEGIN_HPP
#define HAMON_RANGES_CRBEGIN_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/iterator/reverse_iterator.hpp>

#if defined(HAMON_USE_STD_RANGES) && defined(HAMON_USE_STD_REVERSE_ITERATOR)

namespace hamon {
namespace ranges {

using std::ranges::crbegin;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/rbegin.hpp>
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

struct crbegin_fn
{
	template <typename T>
	HAMON_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			ranges::rbegin(ranges::detail::as_const(std::forward<T>(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::crbegin_fn crbegin{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_CRBEGIN_HPP