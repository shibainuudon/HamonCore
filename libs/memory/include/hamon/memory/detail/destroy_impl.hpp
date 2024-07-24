/**
 *	@file	destroy_impl.hpp
 *
 *	@brief	destroy_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_DESTROY_IMPL_HPP
#define HAMON_MEMORY_DETAIL_DESTROY_IMPL_HPP

#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Iterator, typename Sentinel,
	typename ValueType = hamon::iter_value_t<Iterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_destructible<ValueType>::value
	>
>
HAMON_CXX14_CONSTEXPR Iterator
destroy_impl2(Iterator first, Sentinel last, hamon::detail::overload_priority<1>)
{
	hamon::ranges::advance(first, last);
	return first;
}

template <typename Iterator, typename Sentinel>
HAMON_CXX14_CONSTEXPR Iterator
destroy_impl2(Iterator first, Sentinel last, hamon::detail::overload_priority<0>)
{
	for (; first != last; ++first)
	{
		hamon::destroy_at(hamon::addressof(*first));
	}
	return first;
}

template <typename Iterator, typename Sentinel>
HAMON_CXX14_CONSTEXPR Iterator
destroy_impl(Iterator first, Sentinel last)
{
	return hamon::detail::destroy_impl2(first, last, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_DESTROY_IMPL_HPP
