/**
 *	@file	nan.hpp
 *
 *	@brief	nan 関数の定義
 */

#ifndef HAMON_CMATH_NAN_HPP
#define HAMON_CMATH_NAN_HPP

#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

/**
 *	@brief	文字列から quiet NaN へ変換する。
 *
 *	@param	arg		NaNの中身を判別するための文字列
 *
 *	@return	シグナルを発生させないNaNを返す。利用可能であれば、argを通じた内容を付加する。
 */
inline float
nanf(const char* arg) HAMON_NOEXCEPT
{
	return std::nanf(arg);
}

inline double
nan(const char* arg) HAMON_NOEXCEPT
{
	return std::nan(arg);
}

inline long double
nanl(const char* arg) HAMON_NOEXCEPT
{
	return std::nanl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_NAN_HPP
