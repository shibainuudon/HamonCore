/**
 *	@file	foot.hpp
 *
 *	@brief	foot の定義
 */

#ifndef HAMON_UNITS_FOOT_HPP
#define HAMON_UNITS_FOOT_HPP

#include <hamon/units/inch.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 国際フィート = 12インチ(正確に0.3048m)
template <typename T> using foot = decltype(inch<T>() * std::ratio<12>());
template <typename T> using feet = foot<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_FOOT_HPP
