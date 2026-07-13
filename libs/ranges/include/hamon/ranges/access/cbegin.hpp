/**
 *	@file	cbegin.hpp
 *
 *	@brief	ranges::cbegin の定義
 */

#ifndef HAMON_RANGES_ACCESS_CBEGIN_HPP
#define HAMON_RANGES_ACCESS_CBEGIN_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::cbegin;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/possibly_const_range.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/iterator/const_iterator.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.4 ranges::cbegin[range.access.cbegin]
struct cbegin_fn
{
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.access.cbegin]/1.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(							// [range.access.cbegin]/1.2
			hamon::const_iterator<decltype(hamon::ranges::begin(hamon::ranges::detail::possibly_const_range(t)))>(
				hamon::ranges::begin(hamon::ranges::detail::possibly_const_range(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.cbegin]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::cbegin_fn cbegin{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_CBEGIN_HPP
