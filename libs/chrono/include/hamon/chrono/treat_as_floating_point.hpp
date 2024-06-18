/**
 *	@file	treat_as_floating_point.hpp
 *
 *	@brief	treat_as_floating_point の定義
 */

#ifndef HAMON_CHRONO_TREAT_AS_FLOATING_POINT_HPP
#define HAMON_CHRONO_TREAT_AS_FLOATING_POINT_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::treat_as_floating_point;

}	// namespace chrono
}	// namespace hamon

#else

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
constexpr bool treat_as_floating_point_v = treat_as_floating_point<Rep>::value;

#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TREAT_AS_FLOATING_POINT_HPP
