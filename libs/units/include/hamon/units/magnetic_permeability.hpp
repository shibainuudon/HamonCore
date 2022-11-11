/**
 *	@file	magnetic_permeability.hpp
 *
 *	@brief	magnetic_permeability の定義
 */

#ifndef HAMON_UNITS_MAGNETIC_PERMEABILITY_HPP
#define HAMON_UNITS_MAGNETIC_PERMEABILITY_HPP

#include <hamon/units/henry.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ヘンリー毎メートル(透磁率の単位)
template <typename T> using henry_per_metre   = decltype(henry<T>() / metre<T>());
template <typename T> using henry_per_meter   = henry_per_metre<T>;
template <typename T> using henries_per_metre = henry_per_metre<T>;
template <typename T> using henries_per_meter = henry_per_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MAGNETIC_PERMEABILITY_HPP
