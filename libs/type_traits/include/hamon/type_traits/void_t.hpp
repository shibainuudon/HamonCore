/**
 *	@file	void_t.hpp
 *
 *	@brief	void_t の定義
 */

#ifndef HAMON_TYPE_TRAITS_VOID_T_HPP
#define HAMON_TYPE_TRAITS_VOID_T_HPP

namespace hamon
{

namespace detail
{

template <typename... Ts>
struct make_void
{
	using type = void;
};

}	// namespace detail

// [meta.trans.other], other transformations

template <typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_VOID_T_HPP
