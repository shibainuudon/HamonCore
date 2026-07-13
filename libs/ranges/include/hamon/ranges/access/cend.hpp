/**
 *	@file	cend.hpp
 *
 *	@brief	ranges::cend の定義
 */

#ifndef HAMON_RANGES_ACCESS_CEND_HPP
#define HAMON_RANGES_ACCESS_CEND_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::cend;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/possibly_const_range.hpp>
#include <hamon/ranges/end.hpp>
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

// 25.3.5 ranges::cend[range.access.cend]
struct cend_fn
{
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.access.cend]/1.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(							// [range.access.cend]/1.2
			hamon::const_sentinel<decltype(hamon::ranges::end(hamon::ranges::detail::possibly_const_range(t)))>(
				hamon::ranges::end(hamon::ranges::detail::possibly_const_range(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.cend]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::cend_fn cend{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_CEND_HPP
