/**
 *	@file	variant_size.hpp
 *
 *	@brief	variant_size の定義
 */

#ifndef HAMON_VARIANT_VARIANT_SIZE_HPP
#define HAMON_VARIANT_VARIANT_SIZE_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::variant_size;
using std::variant_size_v;

}	// namespace hamon

#else

#include <hamon/variant/variant_fwd.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [variant.helper], variant helper classes
template <typename T>
struct variant_size;	// not defined

template <typename T>
struct variant_size<T const>
	: public variant_size<T>{};

#if 0	// deprecated in C++20
template <typename T>
struct variant_size<T volatile>;

template <typename T>
struct variant_size<T const volatile>;
#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR hamon::size_t
variant_size_v = variant_size<T>::value;

#endif

// [variant.helper]/2
template <typename... Types>
struct variant_size<variant<Types...>>
	: public hamon::integral_constant<hamon::size_t, sizeof...(Types)> {};

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_VARIANT_SIZE_HPP
