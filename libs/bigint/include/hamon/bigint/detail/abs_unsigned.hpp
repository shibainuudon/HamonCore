/**
 *	@file	abs_unsigned.hpp
 *
 *	@brief	abs_unsigned 関数の定義
 */

#ifndef HAMON_BIGINT_DETAIL_ABS_UNSIGNED_HPP
#define HAMON_BIGINT_DETAIL_ABS_UNSIGNED_HPP

#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
abs_unsigned_impl(bool minus, T x)
{
	return minus ? static_cast<T>(~x + 1) : x;
}

}	// namespace detail

template <typename T>
inline HAMON_CXX11_CONSTEXPR hamon::make_unsigned_t<T>
abs_unsigned(T x)
{
	return detail::abs_unsigned_impl(x < 0, static_cast<hamon::make_unsigned_t<T>>(x));
}

}	// namespace hamon

#endif // HAMON_BIGINT_DETAIL_ABS_UNSIGNED_HPP
