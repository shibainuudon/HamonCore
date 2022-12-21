/**
 *	@file	round_half_even.hpp
 *
 *	@brief	ranges::round_half_even の定義
 */

#ifndef HAMON_CMATH_RANGES_ROUND_HALF_EVEN_HPP
#define HAMON_CMATH_RANGES_ROUND_HALF_EVEN_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_round_half_even.hpp>
#include <hamon/cmath/round_half_even.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace round_half_even_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct round_half_even_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_adl_round_half_even, T)>
	static HAMON_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(round_half_even(x))

	template <typename T>
	static HAMON_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::round_half_even(x))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T const& x) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace round_half_even_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
round_half_even_detail::round_half_even_fn round_half_even{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_ROUND_HALF_EVEN_HPP
