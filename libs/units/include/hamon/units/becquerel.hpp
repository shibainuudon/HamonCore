/**
 *	@file	becquerel.hpp
 *
 *	@brief	becquerel の定義
 */

#ifndef HAMON_UNITS_BECQUEREL_HPP
#define HAMON_UNITS_BECQUEREL_HPP

#include <hamon/units/second.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ベクレル(放射性核種の放射能を表す単位)
template <typename T> using becquerel  = decltype(T() / second<T>());
template <typename T> using becquerels = becquerel<T>;
HAMON_UNITS_SI_PREFIX(becquerel);
HAMON_UNITS_SI_PREFIX(becquerels);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BECQUEREL_HPP
