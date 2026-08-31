/**
 *	@file	treat_as_floating_point.hpp
 *
 *	@brief	treat_as_floating_point の定義
 */

#ifndef HAMON_CHRONO_TREAT_AS_FLOATING_POINT_HPP
#define HAMON_CHRONO_TREAT_AS_FLOATING_POINT_HPP

#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 29.4.1 treat_as_floating_point[time.traits.is.fp]

template <typename Rep>
struct treat_as_floating_point
	: public hamon::is_floating_point<Rep> {};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename Rep>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool treat_as_floating_point_v = treat_as_floating_point<Rep>::value;

#endif

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_TREAT_AS_FLOATING_POINT_HPP
