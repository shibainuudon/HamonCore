/**
 *	@file	pow.hpp
 *
 *	@brief	ranges::pow の定義
 */

#ifndef HAMON_CMATH_RANGES_POW_HPP
#define HAMON_CMATH_RANGES_POW_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_pow.hpp>
#include <hamon/cmath/pow.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace pow_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct pow_fn
{
private:
	template <typename T1, typename T2,
		typename = hamon::enable_if_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
			has_adl_pow<T1, T2>
#else
			has_adl_pow<T1, T2>::value
#endif
		>
	>
	static HAMON_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(pow(x, y))

	template <typename T1, typename T2>
	static HAMON_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::pow(x, y))

public:
	template <typename T1, typename T2>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T1 const& x, T2 const& y) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, y, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace pow_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
pow_detail::pow_fn pow{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_POW_HPP
