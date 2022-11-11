/**
 *	@file	furlong.hpp
 *
 *	@brief	furlong の定義
 */

#ifndef HAMON_UNITS_FURLONG_HPP
#define HAMON_UNITS_FURLONG_HPP

#include <hamon/units/foot.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 国際ハロン = 660フィート (正確に201.168m)
template <typename T> using furlong  = decltype(foot<T>() * std::ratio<660>());
template <typename T> using furlongs = furlong<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_FURLONG_HPP
