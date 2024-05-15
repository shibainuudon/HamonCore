/**
 *	@file	destroy.hpp
 *
 *	@brief	destroy を定義
 */

#ifndef HAMON_MEMORY_DESTROY_HPP
#define HAMON_MEMORY_DESTROY_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::destroy;

}	// namespace hamon

#else

#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_destructible<ValueType>::value
	>
>
HAMON_CXX20_CONSTEXPR void
destroy_impl(ForwardIterator, ForwardIterator, hamon::detail::overload_priority<1>)
{
}

template <typename ForwardIterator>
HAMON_CXX20_CONSTEXPR void
destroy_impl(ForwardIterator first, ForwardIterator last, hamon::detail::overload_priority<0>)
{
	for (; first != last; ++first)
	{
		hamon::destroy_at(hamon::addressof(*first));
	}
}

}	// namespace detail

template <typename ForwardIterator>
HAMON_CXX20_CONSTEXPR void
destroy(ForwardIterator first, ForwardIterator last)
{
	detail::destroy_impl(first, last, hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_HPP
