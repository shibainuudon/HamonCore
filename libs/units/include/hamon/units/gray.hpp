/**
 *	@file	gray.hpp
 *
 *	@brief	gray の定義
 */

#ifndef HAMON_UNITS_GRAY_HPP
#define HAMON_UNITS_GRAY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/gram.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// グレイ(吸収線量の単位)
template <typename T> using gray  = decltype(joule<T>() / kilogram<T>());
template <typename T> using grays = gray<T>;
HAMON_UNITS_SI_PREFIX(gray);
HAMON_UNITS_SI_PREFIX(grays);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_GRAY_HPP
