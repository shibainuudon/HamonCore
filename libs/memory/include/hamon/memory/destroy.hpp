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

#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.11.9 destroy[specialized.destroy]

template <typename NoThrowForwardIterator>
HAMON_CXX20_CONSTEXPR void
destroy(NoThrowForwardIterator first, NoThrowForwardIterator last)
{
	hamon::detail::destroy_impl(first, last);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_HPP
