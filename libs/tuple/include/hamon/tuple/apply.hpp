/**
 *	@file	apply.hpp
 *
 *	@brief	apply の定義
 */

#ifndef HAMON_TUPLE_APPLY_HPP
#define HAMON_TUPLE_APPLY_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::apply;

}	// namespace hamon

#else

#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/tuple_size.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace tuple_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename F, typename Tuple, hamon::size_t... I>
HAMON_CXX11_CONSTEXPR auto
apply_impl(F&& f, Tuple&& t, hamon::index_sequence<I...>)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::invoke(
		hamon::forward<F>(f),
		hamon::adl_get<I>(hamon::forward<Tuple>(t))...))

}	// namespace tuple_detail

// Calling a function with a tuple of arguments	[tuple.apply]
template <typename F, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, Tuple)>
HAMON_CXX11_CONSTEXPR auto
apply(F&& f, Tuple&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	tuple_detail::apply_impl(
		hamon::forward<F>(f),
		hamon::forward<Tuple>(t),
		hamon::make_index_sequence<hamon::tuple_size<hamon::remove_reference_t<Tuple>>::value>{}))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_APPLY_HPP
