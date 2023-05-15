/**
 *	@file	tuple_impl.hpp
 *
 *	@brief	tuple_impl の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_IMPL_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_IMPL_HPP

#include <hamon/tuple/tuple_fwd.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/detail/tuple_leaf.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/adl_swap.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace tuple_detail {

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_GCC("-Wfloat-conversion")

template <typename IndexSequence, typename... Types>
struct tuple_impl;

template <hamon::size_t... Is, typename... Types>
struct tuple_impl<hamon::index_sequence<Is...>, Types...>
	: tuple_leaf<Is, Types>...
{
	HAMON_CXX11_CONSTEXPR
	tuple_impl()
	{}

	template <typename... UTypes>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(ctor_from_elems_tag, UTypes&&... args)
		: tuple_leaf<Is, Types>(hamon::forward<UTypes>(args))...
	{}

	template <typename UTuple>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(ctor_from_tuple_tag, UTuple&& u)
		: tuple_leaf<Is, Types>(hamon::adl_get<Is>(hamon::forward<UTuple>(u)))...
	{}

	template <typename Alloc>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::allocator_arg_t, Alloc const& a)
		: tuple_leaf<Is, Types>(hamon::allocator_arg_t{}, a)...
	{}

	template <typename Alloc, typename... UTypes>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::allocator_arg_t, Alloc const& a, ctor_from_elems_tag, UTypes&&... args)
		: tuple_leaf<Is, Types>(hamon::allocator_arg_t{}, a, hamon::forward<UTypes>(args))...
	{}

	template <typename Alloc, typename UTuple>
	HAMON_CXX11_CONSTEXPR
	tuple_impl(hamon::allocator_arg_t, Alloc const& a, ctor_from_tuple_tag, UTuple&& u)
		: tuple_leaf<Is, Types>(hamon::allocator_arg_t{}, a, hamon::adl_get<Is>(hamon::forward<UTuple>(u)))...
	{}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR
	static void swallow(Args&&...) HAMON_NOEXCEPT {}

	template <typename TTuple, typename... UTypes>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, tuple<UTypes...> const& rhs)
	{
		swallow(((hamon::adl_get<Is>(lhs) = hamon::adl_get<Is>(rhs)), 0)...);
	}

	template <typename TTuple, typename... UTypes>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, tuple<UTypes...>&& rhs)
	{
		swallow(((hamon::adl_get<Is>(lhs) = hamon::forward<UTypes>(hamon::adl_get<Is>(rhs))), 0)...);
	}

	template <typename TTuple, typename U1, typename U2>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, pair<U1, U2> const& rhs)
	{
		hamon::adl_get<0>(lhs) = rhs.first;
		hamon::adl_get<1>(lhs) = rhs.second;
	}

	template <typename TTuple, typename U1, typename U2>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, pair<U1, U2>&& rhs)
	{
		hamon::adl_get<0>(lhs) = hamon::forward<U1>(rhs.first);
		hamon::adl_get<1>(lhs) = hamon::forward<U2>(rhs.second);
	}
	
	template <typename TTuple, typename UTuple>
	HAMON_CXX14_CONSTEXPR
	static void assign(TTuple& lhs, UTuple&& rhs)
	{
		swallow(((hamon::adl_get<Is>(lhs) = hamon::adl_get<Is>(hamon::forward<UTuple>(rhs))), 0)...);
	}

	template <typename TTuple, typename UTuple>
	HAMON_CXX14_CONSTEXPR
	static void swap(TTuple& lhs, UTuple& rhs)
	{
		swallow((hamon::adl_swap(hamon::adl_get<Is>(lhs), hamon::adl_get<Is>(rhs)), 0)...);
	}
};

template <typename... Types>
using tuple_impl_t =
	tuple_impl<hamon::make_index_sequence<sizeof...(Types)>, Types...>;

HAMON_WARNING_POP()

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_IMPL_HPP
