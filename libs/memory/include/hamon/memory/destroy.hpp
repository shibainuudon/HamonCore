/**
 *	@file	destroy.hpp
 *
 *	@brief	destroy を定義
 */

#ifndef HAMON_MEMORY_DESTROY_HPP
#define HAMON_MEMORY_DESTROY_HPP

#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.11.9 destroy[specialized.destroy]

template <typename NoThrowForwardIterator>
HAMON_CXX14_CONSTEXPR void
destroy(NoThrowForwardIterator first, NoThrowForwardIterator last)
{
	hamon::detail::destroy_impl(first, last);
}

}	// namespace hamon

#endif // HAMON_MEMORY_DESTROY_HPP
