/**
 *	@file	cdata.hpp
 *
 *	@brief	ranges::cdata の定義
 */

#ifndef HAMON_RANGES_CDATA_HPP
#define HAMON_RANGES_CDATA_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::cdata;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/data.hpp>
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

struct cdata_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			ranges::data(ranges::detail::as_const(std::forward<T>(t))))
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

#endif // HAMON_RANGES_CDATA_HPP
