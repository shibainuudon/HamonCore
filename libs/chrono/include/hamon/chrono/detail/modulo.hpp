﻿/**
 *	@file	modulo.hpp
 *
 *	@brief	modulo の定義
 */

#ifndef HAMON_CHRONO_DETAIL_MODULO_HPP
#define HAMON_CHRONO_DETAIL_MODULO_HPP

#include <hamon/config.hpp>

namespace hamon {
namespace chrono {
namespace detail {

inline HAMON_CXX11_CONSTEXPR long long
modulo(long long n, int m) HAMON_NOEXCEPT
{
	return n - ((n >= 0 ? n : n - m + 1) / m) * m;
}

struct div_mod_result
{
	long long div;
	long long mod;
};

inline HAMON_CXX11_CONSTEXPR div_mod_result
div_mod(long long n, int m) HAMON_NOEXCEPT
{
	return
	{
		(n >= 0 ? n : n - m + 1) / m,
		n - ((n >= 0 ? n : n - m + 1) / m) * m
	};
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_MODULO_HPP
