/**
 *	@file	destroy_n.hpp
 *
 *	@brief	destroy_n を定義
 */

#ifndef HAMON_MEMORY_DESTROY_N_HPP
#define HAMON_MEMORY_DESTROY_N_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::destroy_n;

}	// namespace hamon

#else

#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/advance.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator, typename Size,
	typename IterValue = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_destructible<IterValue>::value
	>
>
HAMON_CXX14_CONSTEXPR ForwardIterator
destroy_n_impl(ForwardIterator first, Size n,
	hamon::detail::overload_priority<1>)
{
	hamon::advance(first, n);
	return first;
}

template <typename ForwardIterator, typename Size>
HAMON_CXX14_CONSTEXPR ForwardIterator
destroy_n_impl(ForwardIterator first, Size n,
	hamon::detail::overload_priority<0>)
{
	// [specialized.destroy]/4

	for (; n > 0; --n)
	{
		hamon::destroy_at(hamon::addressof(*first));
		++first;
	}

	return first;
}

}	// namespace detail

// 27.11.9 destroy[specialized.destroy]

template <typename NoThrowForwardIterator, typename Size>
HAMON_CXX14_CONSTEXPR NoThrowForwardIterator
destroy_n(NoThrowForwardIterator first, Size n)
{
	return hamon::detail::destroy_n_impl(
		first, n, hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_N_HPP
