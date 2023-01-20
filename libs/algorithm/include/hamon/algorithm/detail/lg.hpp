/**
 *	@file	lg.hpp
 *
 *	@brief	lg の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_LG_HPP
#define HAMON_ALGORITHM_DETAIL_LG_HPP

#include <hamon/bit/countl_zero.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR T lg(T n)
{
	HAMON_ASSERT(n > 0);
	using UT = hamon::make_unsigned_t<T>;
	return static_cast<T>(
		hamon::bitsof<T>()
		- static_cast<std::size_t>(1)
		- static_cast<std::size_t>(hamon::countl_zero(static_cast<UT>(n))));
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_LG_HPP
