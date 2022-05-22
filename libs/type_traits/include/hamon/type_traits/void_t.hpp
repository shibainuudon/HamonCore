/**
 *	@file	void_t.hpp
 *
 *	@brief	void_t の定義
 */

#ifndef HAMON_TYPE_TRAITS_VOID_T_HPP
#define HAMON_TYPE_TRAITS_VOID_T_HPP

#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_void_t) && (__cpp_lib_void_t >= 201411L)

using std::void_t;

#else

namespace detail
{

template <typename... Ts>
struct make_void
{
	using type = void;
};

}	// namespace detail

template <typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_VOID_T_HPP
