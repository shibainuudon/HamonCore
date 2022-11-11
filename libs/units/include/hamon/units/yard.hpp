/**
 *	@file	yard.hpp
 *
 *	@brief	yard の定義
 */

#ifndef HAMON_UNITS_YARD_HPP
#define HAMON_UNITS_YARD_HPP

#include <hamon/units/foot.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 国際ヤード = 3フィート (正確に0.9144m)
template <typename T> using yard  = decltype(foot<T>() * std::ratio<3>());
template <typename T> using yards = yard<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_YARD_HPP
