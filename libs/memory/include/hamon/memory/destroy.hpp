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
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR void
destroy_impl(ForwardIterator first, ForwardIterator last, std::false_type)
{
	for (; first != last; ++first)
	{
		hamon::destroy_at(hamon::addressof(*first));
	}
}

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR void
destroy_impl(ForwardIterator, ForwardIterator, std::true_type)
{
}

}	// namespace detail

template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR void
destroy(ForwardIterator first, ForwardIterator last)
{
	using value_t = hamon::iter_value_t<ForwardIterator>;
	detail::destroy_impl(first, last, std::is_trivially_destructible<value_t>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_HPP
