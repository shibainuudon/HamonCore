/**
 *	@file	are.hpp
 *
 *	@brief	are の定義
 */

#ifndef HAMON_UNITS_ARE_HPP
#define HAMON_UNITS_ARE_HPP

#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// アール(100 平方メートル)
template <typename T> using are  = decltype(decametre<T>() * decametre<T>());
template <typename T> using ares = are<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ARE_HPP
