/**
 *	@file	fpclassify.hpp
 *
 *	@brief	fpclassify 関数の定義
 */

#ifndef HAMON_CMATH_FPCLASSIFY_HPP
#define HAMON_CMATH_FPCLASSIFY_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::fpclassify;

}	// namespace hamon

#else

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/issubnormal.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR int
fpclassify_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::fpclassify(x);
	}
#endif
	return
		hamon::isnan(x) ?
			FP_NAN :
		hamon::isinf(x) ?
			FP_INFINITE :
		hamon::iszero(x) ?
			FP_ZERO :
		hamon::issubnormal(x) ?
			FP_SUBNORMAL :
		FP_NORMAL;
}

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int
fpclassify(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::fpclassify_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_FPCLASSIFY_HPP
