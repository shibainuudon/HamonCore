/**
 *	@file	in_place_type_t.hpp
 *
 *	@brief	in_place_type_t を定義
 */

#ifndef HAMON_UTILITY_IN_PLACE_TYPE_T_HPP
#define HAMON_UTILITY_IN_PLACE_TYPE_T_HPP

#include <hamon/config.hpp>

#if HAMON_CXX_STANDARD >= 17

#include <utility>

namespace hamon
{

using std::in_place_type_t;
using std::in_place_type;

}	// namespace hamon

#else	// HAMON_CXX_STANDARD >= 17

namespace hamon
{

// in_place_type_t
template <typename T>
struct in_place_type_t
{
	explicit in_place_type_t() = default;
};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_STATIC_CONSTEXPR hamon::in_place_type_t<T> in_place_type{};

#endif	// defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace hamon

#endif	// HAMON_CXX_STANDARD >= 17

#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/bool_constant.hpp>

// is_in_place_type

namespace hamon
{

namespace detail
{

template <typename T>
struct is_in_place_type_impl
	: public hamon::false_type
{};

template <typename T>
struct is_in_place_type_impl<hamon::in_place_type_t<T>>
	: public hamon::true_type
{};

}	// namespace detail

template <typename T>
using is_in_place_type =
	detail::is_in_place_type_impl<hamon::remove_cvref_t<T>>;

}	// namespace hamon

#endif // HAMON_UTILITY_IN_PLACE_TYPE_T_HPP
