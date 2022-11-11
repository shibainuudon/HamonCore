/**
 *	@file	mile.hpp
 *
 *	@brief	mile の定義
 */

#ifndef HAMON_UNITS_MILE_HPP
#define HAMON_UNITS_MILE_HPP

#include <hamon/units/yard.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 国際マイル = 1760ヤード  (正確に1609.344m)
template <typename T> using mile  = decltype(yard<T>() * std::ratio<1760>());
template <typename T> using miles = mile<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MILE_HPP
