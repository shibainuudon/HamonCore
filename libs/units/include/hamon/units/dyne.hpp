/**
 *	@file	dyne.hpp
 *
 *	@brief	dyne の定義
 */

#ifndef HAMON_UNITS_DYNE_HPP
#define HAMON_UNITS_DYNE_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/gram.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ダイン(g・cm/s^2)
template <typename T> using dyne  = decltype(gram<T>() * centimetre<T>() / second<T>() / second<T>());
template <typename T> using dynes = dyne<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DYNE_HPP
