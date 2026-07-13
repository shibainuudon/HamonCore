/**
 *	@file	crend.hpp
 *
 *	@brief	ranges::crend の定義
 */

#ifndef HAMON_RANGES_ACCESS_CREND_HPP
#define HAMON_RANGES_ACCESS_CREND_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/iterator/reverse_iterator.hpp>

#if defined(HAMON_USE_STD_RANGES) && defined(HAMON_USE_STD_REVERSE_ITERATOR)

namespace hamon {
namespace ranges {

using std::ranges::crend;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/possibly_const_range.hpp>
#include <hamon/ranges/rend.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/iterator/const_sentinel.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.9 ranges::crend[range.access.crend]
struct crend_fn
{
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.access.crend]/1.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(							// [range.access.crend]/1.2
			hamon::const_sentinel<decltype(hamon::ranges::rend(hamon::ranges::detail::possibly_const_range(t)))>(
				hamon::ranges::rend(hamon::ranges::detail::possibly_const_range(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.crend]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::crend_fn crend{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_CREND_HPP
