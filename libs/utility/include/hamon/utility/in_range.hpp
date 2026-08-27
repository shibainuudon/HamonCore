/**
 *	@file	in_range.hpp
 *
 *	@brief	in_range を定義
 */

#ifndef HAMON_UTILITY_IN_RANGE_HPP
#define HAMON_UTILITY_IN_RANGE_HPP

#include <hamon/utility/detail/is_standard_integer.hpp>
#include <hamon/utility/cmp_greater_equal.hpp>
#include <hamon/utility/cmp_less_equal.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.7 Integer comparison functions[utility.intcmp]

template <typename R, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
in_range(T t) HAMON_NOEXCEPT
{
	// [utility.intcmp]/9
	static_assert(hamon::detail::is_standard_integer<R>::value, "");
	static_assert(hamon::detail::is_standard_integer<T>::value, "");

	// [utility.intcmp]/10
	return
		hamon::cmp_greater_equal(t, hamon::numeric_limits<R>::min()) &&
		hamon::cmp_less_equal(t, hamon::numeric_limits<R>::max());
}

}	// namespace hamon

#endif // HAMON_UTILITY_IN_RANGE_HPP
