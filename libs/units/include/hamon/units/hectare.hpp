/**
 *	@file	hectare.hpp
 *
 *	@brief	hectare の定義
 */

#ifndef HAMON_UNITS_HECTARE_HPP
#define HAMON_UNITS_HECTARE_HPP

#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ヘクタール(10,000 平方メートル)
template <typename T> using hectare  = decltype(hectometre<T>() * hectometre<T>());
template <typename T> using hectares = hectare<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_HECTARE_HPP
