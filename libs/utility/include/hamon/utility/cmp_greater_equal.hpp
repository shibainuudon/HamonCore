/**
 *	@file	cmp_greater_equal.hpp
 *
 *	@brief	cmp_greater_equal を定義
 */

#ifndef HAMON_UTILITY_CMP_GREATER_EQUAL_HPP
#define HAMON_UTILITY_CMP_GREATER_EQUAL_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace hamon
{

using std::cmp_greater_equal;

}	// namespace hamon

#else

#include <hamon/utility/cmp_less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename U>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
cmp_greater_equal(T t, U u) HAMON_NOEXCEPT
{
	return !hamon::cmp_less(t, u);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_CMP_GREATER_EQUAL_HPP
