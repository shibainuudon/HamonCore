/**
 *	@file	action.hpp
 *
 *	@brief	action の定義
 */

#ifndef HAMON_UNITS_ACTION_HPP
#define HAMON_UNITS_ACTION_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ジュール秒(作用の単位)
template <typename T> using joule_second  = decltype(joule<T>() * second<T>());
template <typename T> using joule_seconds = joule_second<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ACTION_HPP
