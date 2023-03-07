/**
 *	@file	in_place_index.hpp
 *
 *	@brief	in_place_index を定義
 */

#ifndef HAMON_UTILITY_IN_PLACE_INDEX_HPP
#define HAMON_UTILITY_IN_PLACE_INDEX_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

#if HAMON_CXX_STANDARD >= 17

#include <utility>

namespace hamon
{

using std::in_place_index_t;
using std::in_place_index;

}	// namespace hamon

#else	// HAMON_CXX_STANDARD >= 17

namespace hamon
{

// in_place_index_t
template <hamon::size_t I>
struct in_place_index_t
{
	explicit in_place_index_t() = default;
};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <hamon::size_t I>
HAMON_STATIC_CONSTEXPR hamon::in_place_index_t<I> in_place_index{};

#endif	// defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace hamon

#endif	// HAMON_CXX_STANDARD >= 17

#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/bool_constant.hpp>

// is_in_place_index

namespace hamon
{

namespace detail
{

template <typename T>
struct is_in_place_index_impl
	: public hamon::false_type
{};

template <hamon::size_t I>
struct is_in_place_index_impl<hamon::in_place_index_t<I>>
	: public hamon::true_type
{};

}	// namespace detail

template <typename T>
using is_in_place_index =
	detail::is_in_place_index_impl<hamon::remove_cvref_t<T>>;

}	// namespace hamon

#endif // HAMON_UTILITY_IN_PLACE_INDEX_HPP
