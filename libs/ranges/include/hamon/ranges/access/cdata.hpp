/**
 *	@file	cdata.hpp
 *
 *	@brief	ranges::cdata の定義
 */

#ifndef HAMON_RANGES_ACCESS_CDATA_HPP
#define HAMON_RANGES_ACCESS_CDATA_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::cdata;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/possibly_const_range.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

// [range.prim.cdata]
template <typename T>
constexpr const T* as_const_pointer(const T* p) noexcept { return p; }

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct cdata_fn
{
	// [range.prim.cdata]
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			as_const_pointer(hamon::ranges::data(possibly_const_range(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::cdata_fn cdata{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_CDATA_HPP
