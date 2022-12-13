/**
 *	@file	ceil.hpp
 *
 *	@brief	ranges::ceil の定義
 */

#ifndef HAMON_CMATH_RANGES_CEIL_HPP
#define HAMON_CMATH_RANGES_CEIL_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_ceil.hpp>
#include <hamon/cmath/ceil.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace ceil_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct ceil_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_adl_ceil, T)>
	static HAMON_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(ceil(x))

	template <typename T>
	static HAMON_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::ceil(x))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T const& x) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace ceil_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
ceil_detail::ceil_fn ceil{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_CEIL_HPP
