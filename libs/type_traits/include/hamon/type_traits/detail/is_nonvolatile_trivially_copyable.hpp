/**
 *	@file	is_nonvolatile_trivially_copyable.hpp
 *
 *	@brief	is_nonvolatile_trivially_copyable の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_NONVOLATILE_TRIVIALLY_COPYABLE_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_NONVOLATILE_TRIVIALLY_COPYABLE_HPP

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_volatile.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

// Cannot use memcpy/memmove/memcmp on volatile types even if they are
// trivially copyable, so ensure is_memcpyable<volatile int*, volatile int*>
// and similar will be false.

template <typename T>
struct is_nonvolatile_trivially_copyable
	: public hamon::conjunction<
		hamon::negation<hamon::is_volatile<T>>,
		std::is_trivially_copyable<T>
	>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_NONVOLATILE_TRIVIALLY_COPYABLE_HPP
