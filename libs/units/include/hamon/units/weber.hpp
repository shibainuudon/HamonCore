/**
 *	@file	weber.hpp
 *
 *	@brief	weber の定義
 */

#ifndef HAMON_UNITS_WEBER_HPP
#define HAMON_UNITS_WEBER_HPP

#include <hamon/units/volt.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ウェーバ(磁束の単位)
template <typename T> using weber  = decltype(volt<T>() * second<T>());
template <typename T> using webers = weber<T>;
HAMON_UNITS_SI_PREFIX(weber);
HAMON_UNITS_SI_PREFIX(webers);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_WEBER_HPP
