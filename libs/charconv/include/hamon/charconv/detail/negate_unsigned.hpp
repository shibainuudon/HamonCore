﻿/**
 *	@file	negate_unsigned.hpp
 *
 *	@brief	negate_unsigned の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_NEGATE_UNSIGNED_HPP
#define HAMON_CHARCONV_DETAIL_NEGATE_UNSIGNED_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace charconv_detail
{

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
inline HAMON_CXX11_CONSTEXPR T
negate_unsigned(T x)
{
	return static_cast<T>(~x + 1);
}

}	// namespace charconv_detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_NEGATE_UNSIGNED_HPP
