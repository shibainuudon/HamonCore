/**
 *	@file	hive_traits.hpp
 *
 *	@brief	hive_traits の定義
 */

#ifndef HAMON_HIVE_DETAIL_HIVE_TRAITS_HPP
#define HAMON_HIVE_DETAIL_HIVE_TRAITS_HPP

#include <hamon/hive/hive_limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct hive_traits
{
	static HAMON_CXX11_CONSTEXPR hamon::hive_limits
	default_limits() HAMON_NOEXCEPT
	{
		return hamon::hive_limits(8, 64);
	}

	static HAMON_CXX11_CONSTEXPR hamon::hive_limits
	hard_limits() HAMON_NOEXCEPT
	{
		return hamon::hive_limits(1, 64 * 64);
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_HIVE_DETAIL_HIVE_TRAITS_HPP
