/**
 *	@file	as_const.hpp
 *
 *	@brief	as_const を定義
 */

#ifndef HAMON_UTILITY_AS_CONST_HPP
#define HAMON_UTILITY_AS_CONST_HPP

#include <utility>

#if defined(__cpp_lib_as_const) && (__cpp_lib_as_const >= 201510)

namespace hamon
{

using std::as_const;

}	// namespace hamon

#else

#include <hamon/type_traits/add_const.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *
 */
template <typename T>
inline HAMON_CONSTEXPR hamon::add_const_t<T>&
as_const(T& t) HAMON_NOEXCEPT
{
	return t;
}

/**
 *
 */
template <typename T>
void as_const(T const&&) = delete;

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_AS_CONST_HPP
