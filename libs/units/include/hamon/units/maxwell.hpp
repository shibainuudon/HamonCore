/**
 *	@file	maxwell.hpp
 *
 *	@brief	maxwell の定義
 */

#ifndef HAMON_UNITS_MAXWELL_HPP
#define HAMON_UNITS_MAXWELL_HPP

#include <hamon/units/volt.hpp>
#include <hamon/units/second.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// マクスウェル(磁束の単位)
template <typename T> using maxwell  = decltype(volt<T>() * second<T>() * hamon::ratio<1, 100000000>());
template <typename T> using maxwells = maxwell<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MAXWELL_HPP
