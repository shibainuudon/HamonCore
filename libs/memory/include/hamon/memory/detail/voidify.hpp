/**
 *	@file	voidify.hpp
 *
 *	@brief	voidify を定義
 */

#ifndef HAMON_MEMORY_DETAIL_VOIDIFY_HPP
#define HAMON_MEMORY_DETAIL_VOIDIFY_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// 26.11.1 General[specialized.algorithms.general]

template <typename T>
HAMON_CXX14_CONSTEXPR void* voidify(T& obj) HAMON_NOEXCEPT
{
	// [specialized.algorithms.general]/4
	return hamon::addressof(obj);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_VOIDIFY_HPP
