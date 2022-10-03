/**
 *	@file	indirect_result_t.hpp
 *
 *	@brief	indirect_result_t の定義
 */

#ifndef HAMON_ITERATOR_INDIRECT_RESULT_T_HPP
#define HAMON_ITERATOR_INDIRECT_RESULT_T_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::indirect_result_t;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename F, typename... Is>
requires
	(hamon::indirectly_readable<Is>&& ...) &&
	 hamon::invocable<F, hamon::iter_reference_t<Is>...>
using indirect_result_t = hamon::invoke_result_t<F, hamon::iter_reference_t<Is>...>;

#else

namespace detail
{

template <typename...>
struct type_pack
{};

// Visual Studio 2017 のバグに対応するため、2段階で解決する
template <typename, typename, typename = void>
struct indirect_result_t_impl_2{};

template <typename F, typename... Is>
struct indirect_result_t_impl_2<F, type_pack<Is...>,
	hamon::enable_if_t<
		hamon::invocable<F, Is...>::value
	>
>
{
	using type = hamon::invoke_result_t<F, Is...>;
};

template <typename, typename, typename = void>
struct indirect_result_t_impl;

template <typename F, typename... Is>
struct indirect_result_t_impl<F, type_pack<Is...>,
	hamon::enable_if_t<
		hamon::conjunction<hamon::indirectly_readable<Is>...>::value
	>
> : public indirect_result_t_impl_2<F, type_pack<hamon::iter_reference_t<Is>...>> {};

}	// namespace detail

template <typename F, typename... Is>
using indirect_result_t = typename detail::indirect_result_t_impl<F, detail::type_pack<Is...>>::type;

#endif

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INDIRECT_RESULT_T_HPP
