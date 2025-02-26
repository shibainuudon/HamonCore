﻿/**
 *	@file	cmath.hpp
 *
 *	@brief	CMath library
 */

#ifndef HAMON_CMATH_HPP
#define HAMON_CMATH_HPP

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/acos.hpp>
#include <hamon/cmath/acosh.hpp>
#include <hamon/cmath/almost_equal.hpp>
#include <hamon/cmath/asin.hpp>
#include <hamon/cmath/asinh.hpp>
#include <hamon/cmath/assoc_laguerre.hpp>
#include <hamon/cmath/assoc_legendre.hpp>
#include <hamon/cmath/atan.hpp>
#include <hamon/cmath/atan2.hpp>
#include <hamon/cmath/atanh.hpp>
#include <hamon/cmath/beta.hpp>
#include <hamon/cmath/cbrt.hpp>
#include <hamon/cmath/ceil.hpp>
#include <hamon/cmath/comp_ellint_1.hpp>
#include <hamon/cmath/comp_ellint_2.hpp>
#include <hamon/cmath/comp_ellint_3.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/cosh.hpp>
//#include <hamon/cmath/cyl_bessel_i.hpp>
//#include <hamon/cmath/cyl_bessel_j.hpp>
//#include <hamon/cmath/cyl_bessel_k.hpp>
//#include <hamon/cmath/cyl_neumann.hpp>
//#include <hamon/cmath/decompose_float.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <hamon/cmath/double_factorial.hpp>
#include <hamon/cmath/ellint_1.hpp>
#include <hamon/cmath/ellint_2.hpp>
#include <hamon/cmath/ellint_3.hpp>
#include <hamon/cmath/erf.hpp>
#include <hamon/cmath/erfc.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/exp2.hpp>
//#include <hamon/cmath/expint.hpp>
#include <hamon/cmath/expm1.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/fdim.hpp>
#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/fma.hpp>
#include <hamon/cmath/fmax.hpp>
#include <hamon/cmath/fmin.hpp>
#include <hamon/cmath/fmod.hpp>
#include <hamon/cmath/fpclassify.hpp>
#include <hamon/cmath/frac.hpp>
#include <hamon/cmath/frexp.hpp>
#include <hamon/cmath/hermite.hpp>
#include <hamon/cmath/hypot.hpp>
#include <hamon/cmath/ilogb.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/isgreater.hpp>
#include <hamon/cmath/isgreaterequal.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isless.hpp>
#include <hamon/cmath/islessequal.hpp>
#include <hamon/cmath/islessgreater.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isnormal.hpp>
#include <hamon/cmath/issubnormal.hpp>
#include <hamon/cmath/isunordered.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/is_even.hpp>
#include <hamon/cmath/is_integer.hpp>
#include <hamon/cmath/is_negative.hpp>
#include <hamon/cmath/is_odd.hpp>
#include <hamon/cmath/is_positive.hpp>
#include <hamon/cmath/laguerre.hpp>
#include <hamon/cmath/ldexp.hpp>
#include <hamon/cmath/legendre.hpp>
#include <hamon/cmath/lerp.hpp>
#include <hamon/cmath/lgamma.hpp>
#include <hamon/cmath/llrint.hpp>
#include <hamon/cmath/llround.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/log10.hpp>
#include <hamon/cmath/log1p.hpp>
#include <hamon/cmath/log2.hpp>
#include <hamon/cmath/logb.hpp>
#include <hamon/cmath/lrint.hpp>
#include <hamon/cmath/lround.hpp>
#include <hamon/cmath/modf.hpp>
#include <hamon/cmath/nan.hpp>
#include <hamon/cmath/nearbyint.hpp>
#include <hamon/cmath/nextafter.hpp>
#include <hamon/cmath/nexttoward.hpp>
#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/radians_to_degrees.hpp>
#include <hamon/cmath/ranges.hpp>
#include <hamon/cmath/remainder.hpp>
#include <hamon/cmath/remquo.hpp>
#include <hamon/cmath/repeat.hpp>
//#include <hamon/cmath/riemann_zeta.hpp>
#include <hamon/cmath/rint.hpp>
#include <hamon/cmath/round.hpp>
#include <hamon/cmath/round_down.hpp>
#include <hamon/cmath/round_half_even.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cmath/rsqrt.hpp>
#include <hamon/cmath/saturate.hpp>
#include <hamon/cmath/scalbln.hpp>
#include <hamon/cmath/scalbn.hpp>
#include <hamon/cmath/sign.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/sinh.hpp>
#include <hamon/cmath/smoothstep.hpp>
#include <hamon/cmath/sph_bessel.hpp>
#include <hamon/cmath/sph_legendre.hpp>
#include <hamon/cmath/sph_neumann.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/step.hpp>
#include <hamon/cmath/tan.hpp>
#include <hamon/cmath/tanh.hpp>
#include <hamon/cmath/tgamma.hpp>
#include <hamon/cmath/trunc.hpp>

#endif // HAMON_CMATH_HPP
