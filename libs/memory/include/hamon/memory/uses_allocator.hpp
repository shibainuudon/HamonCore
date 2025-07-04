/**
 *	@file	uses_allocator.hpp
 *
 *	@brief	uses_allocator の定義
 */

#ifndef HAMON_MEMORY_USES_ALLOCATOR_HPP
#define HAMON_MEMORY_USES_ALLOCATOR_HPP

#include <hamon/config.hpp>
#include <memory>

namespace hamon
{

// [allocator.uses], uses_allocator
template <typename T, typename Alloc>
struct uses_allocator : public std::uses_allocator<T, Alloc> {};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

// [allocator.uses.trait], uses_allocator
template <typename T, typename Alloc>
constexpr bool uses_allocator_v = uses_allocator<T, Alloc>::value;

#endif

}	// namespace hamon

#endif // HAMON_MEMORY_USES_ALLOCATOR_HPP
