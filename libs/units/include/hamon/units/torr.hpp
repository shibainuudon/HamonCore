/**
 *	@file	torr.hpp
 *
 *	@brief	torr の定義
 */

#ifndef HAMON_UNITS_TORR_HPP
#define HAMON_UNITS_TORR_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/pascal.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// トル = 101325 / 760 パスカル
template <typename T> using torr  = decltype(pascals<T>() * hamon::ratio<101325, 760>());
template <typename T> using torrs = torr<T>;
HAMON_UNITS_SI_PREFIX(torr);
HAMON_UNITS_SI_PREFIX(torrs);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_TORR_HPP
