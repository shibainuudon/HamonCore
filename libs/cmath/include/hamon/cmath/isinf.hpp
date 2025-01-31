/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf
 */

#ifndef HAMON_CMATH_ISINF_HPP
#define HAMON_CMATH_ISINF_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::isinf;

}	// namespace hamon

#else

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isinf_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isinf(x);
#else
	return
		x ==  hamon::numeric_limits<FloatType>::infinity() ||
		x == -hamon::numeric_limits<FloatType>::infinity();
#endif
}

}	// namespace detail

/**
 *	@brief	std::isinf のconstexpr版
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isinf(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isinf_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_ISINF_HPP
