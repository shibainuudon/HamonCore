/**
 *	@file	tonne.hpp
 *
 *	@brief	tonne の定義
 */

#ifndef HAMON_UNITS_TONNE_HPP
#define HAMON_UNITS_TONNE_HPP

#include <hamon/units/gram.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// トン(メトリックトン) = 1000kg
template <typename T> using tonne  = decltype(kilogram<T>() * hamon::ratio<1000>());
template <typename T> using tonnes = tonne<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_TONNE_HPP
