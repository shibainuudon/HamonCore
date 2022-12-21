/**
 *	@file	smoothstep.hpp
 *
 *	@brief	ranges::smoothstep の定義
 */

#ifndef HAMON_CMATH_RANGES_SMOOTHSTEP_HPP
#define HAMON_CMATH_RANGES_SMOOTHSTEP_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_smoothstep.hpp>
#include <hamon/cmath/smoothstep.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace smoothstep_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct smoothstep_fn
{
private:
	template <typename T1, typename T2, typename T3,
		typename = hamon::enable_if_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
			has_adl_smoothstep<T1, T2, T3>
#else
			has_adl_smoothstep<T1, T2, T3>::value
#endif
		>
	>
	static HAMON_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, T3 const& z, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(smoothstep(x, y, z))

	template <typename T1, typename T2, typename T3>
	static HAMON_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, T3 const& z, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::smoothstep(x, y, z))

public:
	template <typename T1, typename T2, typename T3>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T1 const& x, T2 const& y, T3 const& z) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, y, z, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace smoothstep_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
smoothstep_detail::smoothstep_fn smoothstep{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_SMOOTHSTEP_HPP
