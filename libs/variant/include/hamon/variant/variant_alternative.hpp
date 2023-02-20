/**
 *	@file	variant_alternative.hpp
 *
 *	@brief	variant_alternative の定義
 */

#ifndef HAMON_VARIANT_VARIANT_ALTERNATIVE_HPP
#define HAMON_VARIANT_VARIANT_ALTERNATIVE_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::variant_alternative;
using std::variant_alternative_t;

}	// namespace hamon

#else

#include <hamon/variant/variant_fwd.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/nth.hpp>

namespace hamon
{

// [variant.helper], variant helper classes
template <hamon::size_t I, typename T>
struct variant_alternative;		// not defined

template <hamon::size_t I, typename T>
using variant_alternative_t = typename variant_alternative<I, T>::type;

template <hamon::size_t I, typename T>
struct variant_alternative<I, T const>
	: public hamon::add_const<variant_alternative_t<I, T>> {};

#if 0	// deprecated in C++20
template <hamon::size_t I, typename T>
struct variant_alternative<I, T volatile>;

template <hamon::size_t I, typename T>
struct variant_alternative<I, T const volatile>;
#endif

template <hamon::size_t I, typename... Types>
struct variant_alternative<I, variant<Types...>>
{
	// [variant.helper]/4
	static_assert(I < sizeof...(Types), "I must be in [0, sizeof...(Types))");

	// [variant.helper]/5
	using type = hamon::nth_t<I, Types...>;
};

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_VARIANT_ALTERNATIVE_HPP
