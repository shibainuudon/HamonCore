﻿/**
 *	@file	round.hpp
 *
 *	@brief	ranges::round の定義
 */

#ifndef HAMON_CMATH_RANGES_ROUND_HPP
#define HAMON_CMATH_RANGES_ROUND_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_round.hpp>
#include <hamon/cmath/round.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace round_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct round_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_adl_round, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(round(x))

	template <typename T>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::round(x))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T const& x) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace round_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
round_detail::round_fn round{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_ROUND_HPP
