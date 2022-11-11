/**
 *	@file	hertz.hpp
 *
 *	@brief	hertz の定義
 */

#ifndef HAMON_UNITS_HERTZ_HPP
#define HAMON_UNITS_HERTZ_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ヘルツ
template <typename T> using hertz = decltype(T() / second<T>());
HAMON_UNITS_SI_PREFIX(hertz);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_HERTZ_HPP
