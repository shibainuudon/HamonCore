/**
 *	@file	cmp_greater.hpp
 *
 *	@brief	cmp_greater を定義
 */

#ifndef HAMON_UTILITY_CMP_GREATER_HPP
#define HAMON_UTILITY_CMP_GREATER_HPP

#include <hamon/utility/cmp_less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.7 Integer comparison functions[utility.intcmp]

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool cmp_greater(T t, U u) HAMON_NOEXCEPT
{
	// [utility.intcmp]/6
	return hamon::cmp_less(u, t);
}

}	// namespace hamon

#endif // HAMON_UTILITY_CMP_GREATER_HPP
