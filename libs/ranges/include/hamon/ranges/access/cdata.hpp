/**
 *	@file	cdata.hpp
 *
 *	@brief	ranges::cdata の定義
 */

#ifndef HAMON_RANGES_ACCESS_CDATA_HPP
#define HAMON_RANGES_ACCESS_CDATA_HPP

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/possibly_const_range.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/concepts/detail/constraint.hpp>
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

// 25.3.15 ranges::cdata[range.prim.cdata]
struct cdata_fn
{
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.prim.cdata]/1.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(							// [range.prim.cdata]/1.2
			as_const_pointer(hamon::ranges::data(possibly_const_range(t))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.prim.cdata]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::cdata_fn cdata{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ACCESS_CDATA_HPP
