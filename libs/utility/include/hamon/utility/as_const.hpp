/**
 *	@file	as_const.hpp
 *
 *	@brief	as_const を定義
 */

#ifndef HAMON_UTILITY_AS_CONST_HPP
#define HAMON_UTILITY_AS_CONST_HPP

#include <hamon/type_traits/add_const.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.5 Function template as_const[utility.as.const]

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::add_const_t<T>& as_const(T& t) HAMON_NOEXCEPT
{
	// [utility.as.const]/1
	return t;
}

// 22.2.1 Header <utility> synopsis[utility.syn]
template <typename T>
void as_const(T const&&) = delete;

}	// namespace hamon

#endif // HAMON_UTILITY_AS_CONST_HPP
