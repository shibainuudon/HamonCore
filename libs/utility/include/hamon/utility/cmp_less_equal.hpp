/**
 *	@file	cmp_less_equal.hpp
 *
 *	@brief	cmp_less_equal を定義
 */

#ifndef HAMON_UTILITY_CMP_LESS_EQUAL_HPP
#define HAMON_UTILITY_CMP_LESS_EQUAL_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace hamon
{

using std::cmp_less_equal;

}	// namespace hamon

#else

#include <hamon/utility/cmp_less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename U>
inline HAMON_CONSTEXPR bool
cmp_less_equal(T t, U u) HAMON_NOEXCEPT
{
	return !hamon::cmp_less(u, t);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_CMP_LESS_EQUAL_HPP
