/**
 *	@file	fabs.hpp
 *
 *	@brief	ranges::fabs の定義
 */

#ifndef HAMON_CMATH_RANGES_FABS_HPP
#define HAMON_CMATH_RANGES_FABS_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_fabs.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace fabs_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct fabs_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_adl_fabs, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(fabs(x))

	template <typename T>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T const& x, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::fabs(x))

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T const& x) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace fabs_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
fabs_detail::fabs_fn fabs{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_FABS_HPP
