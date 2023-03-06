/**
 *	@file	is_memcpyable.hpp
 *
 *	@brief	is_memcpyable の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_MEMCPYABLE_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_MEMCPYABLE_HPP

#include <hamon/type_traits/detail/is_nonvolatile_trivially_copyable.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

// Whether two iterator types can be used with memcpy/memmove.
template <typename OutputIter, typename InputIter>
struct is_memcpyable : public hamon::false_type {};

template <typename T>
struct is_memcpyable<T*, T*>
	: public detail::is_nonvolatile_trivially_copyable<T>
{};

template <typename T>
struct is_memcpyable<T*, const T*>
	: public detail::is_nonvolatile_trivially_copyable<T>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_MEMCPYABLE_HPP
