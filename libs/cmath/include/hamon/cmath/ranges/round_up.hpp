/**
 *	@file	round_up.hpp
 *
 *	@brief	ranges::round_up の定義
 */

#ifndef HAMON_CMATH_RANGES_ROUND_UP_HPP
#define HAMON_CMATH_RANGES_ROUND_UP_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_round_up.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace round_up_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct round_up_fn
{
private:
	template <typename T1, typename T2,
		typename = hamon::enable_if_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
			has_adl_round_up<T1, T2>
#else
			has_adl_round_up<T1, T2>::value
#endif
		>
	>
	static HAMON_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(round_up(x, y))

	template <typename T1, typename T2>
	static HAMON_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::round_up(x, y))

public:
	template <typename T1, typename T2>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T1 const& x, T2 const& y) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, y, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace round_up_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
round_up_detail::round_up_fn round_up{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_ROUND_UP_HPP
