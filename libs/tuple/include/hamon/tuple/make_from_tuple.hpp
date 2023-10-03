/**
 *	@file	make_from_tuple.hpp
 *
 *	@brief	make_from_tuple の定義
 */

#ifndef HAMON_TUPLE_MAKE_FROM_TUPLE_HPP
#define HAMON_TUPLE_MAKE_FROM_TUPLE_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::make_from_tuple;

}	// namespace hamon

#else

#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/reference_constructs_from_temporary.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#define HAMON_NOEXCEPT_RETURN(...)		\
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)	\
	{ return __VA_ARGS__; }

namespace tuple_detail
{

template <typename T, typename Tuple, hamon::size_t N = std::tuple_size<hamon::remove_reference_t<Tuple>>::value>
struct make_from_tuple_dangling_check
{
	HAMON_STATIC_CONSTEXPR bool value = true;
};

template <typename T, typename Tuple>
struct make_from_tuple_dangling_check<T, Tuple, 1>
{
	// [tuple.apply]/3
#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
	using E = decltype(hamon::adl_get<0>(hamon::declval<Tuple>()));
	HAMON_STATIC_CONSTEXPR bool value = !hamon::reference_constructs_from_temporary<T, E>::value;
#else
	HAMON_STATIC_CONSTEXPR bool value = true;
#endif
};

// [tuple.apply]/4
template <typename T, typename Tuple, hamon::size_t... I>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_constructible<T, decltype(hamon::adl_get<I>(hamon::declval<Tuple>()))...>::value
#endif
inline HAMON_CXX11_CONSTEXPR T
make_from_tuple_impl(Tuple&& t, hamon::index_sequence<I...>)
HAMON_NOEXCEPT_IF_EXPR(T(hamon::adl_get<I>(hamon::forward<Tuple>(t))...))
{
	static_assert(make_from_tuple_dangling_check<T, Tuple>::value, "reference constructs from temporary");
	return T(hamon::adl_get<I>(hamon::forward<Tuple>(t))...);
}

}	// namespace tuple_detail

// Calling a function with a tuple of arguments	[tuple.make_from_tuple]

// [tuple.apply]/4
template <typename T, HAMON_CONSTRAINED_PARAM(hamon::tuple_like, Tuple)>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T
make_from_tuple(Tuple&& t)
HAMON_NOEXCEPT_RETURN(
	tuple_detail::make_from_tuple_impl<T>(
		hamon::forward<Tuple>(t),
		hamon::make_index_sequence<std::tuple_size<hamon::remove_reference_t<Tuple>>::value>{}))

#undef HAMON_NOEXCEPT_RETURN

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_MAKE_FROM_TUPLE_HPP
