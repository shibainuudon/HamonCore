/**
 *	@file	tesla.hpp
 *
 *	@brief	tesla の定義
 */

#ifndef HAMON_UNITS_TESLA_HPP
#define HAMON_UNITS_TESLA_HPP

#include <hamon/units/weber.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// テスラ(磁束密度の単位)
template <typename T> using tesla  = decltype(weber<T>() / metre<T>() / metre<T>());
template <typename T> using teslas = tesla<T>;
HAMON_UNITS_SI_PREFIX(tesla);
HAMON_UNITS_SI_PREFIX(teslas);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_TESLA_HPP
