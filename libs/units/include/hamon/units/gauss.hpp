/**
 *	@file	gauss.hpp
 *
 *	@brief	gauss の定義
 */

#ifndef HAMON_UNITS_GAUSS_HPP
#define HAMON_UNITS_GAUSS_HPP

#include <hamon/units/maxwell.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ガウス(磁束密度の単位)
template <typename T> using gauss   = decltype(maxwell<T>() / centimetre<T>() / centimetre<T>());
template <typename T> using gausses = gauss<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_GAUSS_HPP
