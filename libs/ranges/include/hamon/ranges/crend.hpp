/**
 *	@file	crend.hpp
 *
 *	@brief	ranges::crend の定義
 */

#ifndef HAMON_RANGES_CREND_HPP
#define HAMON_RANGES_CREND_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/iterator/reverse_iterator.hpp>

#if defined(HAMON_USE_STD_RANGES) && defined(HAMON_USE_STD_REVERSE_ITERATOR) &&	\
	defined(__cpp_lib_ranges_as_const) && (__cpp_lib_ranges_as_const >= 202207L)

namespace hamon {
namespace ranges {

using std::ranges::crend;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/possibly_const_range.hpp>
#include <hamon/ranges/rend.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/const_sentinel.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct crend_fn
{
	// [range.access.crend]
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::const_sentinel<decltype(hamon::ranges::rend(hamon::ranges::detail::possibly_const_range(t)))>(
				hamon::ranges::rend(hamon::ranges::detail::possibly_const_range(t))))
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
