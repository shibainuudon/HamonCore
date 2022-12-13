/**
 *	@file	fma.hpp
 *
 *	@brief	ranges::fma の定義
 */

#ifndef HAMON_CMATH_RANGES_FMA_HPP
#define HAMON_CMATH_RANGES_FMA_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_fma.hpp>
#include <hamon/cmath/fma.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace fma_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct fma_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_adl_fma, T)>
	static HAMON_CONSTEXPR auto
	impl(T const& x, T const& y, T const& z, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(fma(x, y, z))

	template <typename T>
	static HAMON_CONSTEXPR auto
	impl(T const& x, T const& y, T const& z, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::fma(x, y, z))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T const& x, T const& y, T const& z) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, y, z, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace fma_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
fma_detail::fma_fn fma{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_FMA_HPP
