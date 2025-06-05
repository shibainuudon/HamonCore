/**
 *	@file	reserve_append_size.hpp
 *
 *	@brief	reserve_append_size の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_RESERVE_APPEND_SIZE_HPP
#define HAMON_CONTAINER_DETAIL_RESERVE_APPEND_SIZE_HPP

#include <hamon/container/detail/is_reservable.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

/*
if constexpr (sized_sentinel_for<Iterator, Iterator>)
{
	if constexpr (is_reservable<Container>::value)
	{
		cont.reserve(cont.size() + ranges::distance(first, last));
	}
}
*/
template <typename Container, typename Iterator,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::is_reservable<Container>,
		hamon::sized_sentinel_for_t<Iterator, Iterator>
	>::value>>
HAMON_CXX14_CONSTEXPR void
reserve_append_size_impl(Container& cont, Iterator first, Iterator last, hamon::detail::overload_priority<1>)
{
	using size_type = typename Container::size_type;
	cont.reserve(cont.size() + static_cast<size_type>(hamon::ranges::distance(first, last)));
}

template <typename Container, typename Iterator>
HAMON_CXX14_CONSTEXPR void
reserve_append_size_impl(Container&, Iterator, Iterator, hamon::detail::overload_priority<0>)
{
}

template <typename Container, typename Iterator>
HAMON_CXX14_CONSTEXPR void
reserve_append_size(Container& cont, Iterator first, Iterator last)
{
	hamon::detail::reserve_append_size_impl(cont, first, last, hamon::detail::overload_priority<1>{});
}

/*
if constexpr (ranges::sized_range<Range>)
{
	if constexpr (is_reservable<Container>::value)
	{
		cont.reserve(cont.size() + ranges::size(rg));
	}
}
*/
template <typename Container, typename Range,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::detail::is_reservable<Container>,
		hamon::ranges::sized_range_t<Range>
	>::value>>
HAMON_CXX14_CONSTEXPR void
reserve_append_size_impl(Container& cont, Range const& rg, hamon::detail::overload_priority<1>)
{
	cont.reserve(cont.size() + hamon::ranges::size(rg));
}

template <typename Container, typename Range>
HAMON_CXX14_CONSTEXPR void
reserve_append_size_impl(Container&, Range const&, hamon::detail::overload_priority<0>)
{
}

template <typename Container, typename Range>
HAMON_CXX14_CONSTEXPR void
reserve_append_size(Container& cont, Range const& rg)
{
	hamon::detail::reserve_append_size_impl(cont, rg, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_RESERVE_APPEND_SIZE_HPP
