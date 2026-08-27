/**
 *	@file	cmp_greater_equal.hpp
 *
 *	@brief	cmp_greater_equal を定義
 */

#ifndef HAMON_UTILITY_CMP_GREATER_EQUAL_HPP
#define HAMON_UTILITY_CMP_GREATER_EQUAL_HPP

#include <hamon/utility/cmp_less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.7 Integer comparison functions[utility.intcmp]

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool cmp_greater_equal(T t, U u) HAMON_NOEXCEPT
{
	// [utility.intcmp]/8
	return !hamon::cmp_less(t, u);
}

}	// namespace hamon

#endif // HAMON_UTILITY_CMP_GREATER_EQUAL_HPP
