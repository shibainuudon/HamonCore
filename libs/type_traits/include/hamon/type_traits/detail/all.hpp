/**
 *	@file	all.hpp
 *
 *	@brief	all の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_ALL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_ALL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>

namespace hamon {
namespace detail {

template <bool... Bs>
struct all : public hamon::conjunction<hamon::bool_constant<Bs>...> {};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <bool... Bs>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool all_v = all<Bs...>::value;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_ALL_HPP
