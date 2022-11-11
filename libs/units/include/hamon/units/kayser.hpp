/**
 *	@file	kayser.hpp
 *
 *	@brief	kayser の定義
 */

#ifndef HAMON_UNITS_KAYSER_HPP
#define HAMON_UNITS_KAYSER_HPP

#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// カイザー
template <typename T> using kayser  = decltype(T() / centimetre<T>());
template <typename T> using kaysers = kayser<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_KAYSER_HPP
