﻿/**
 *	@file	uninitialized_value_construct.hpp
 *
 *	@brief	uninitialized_value_construct を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_HPP
#define HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_value_construct;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_value_construct_impl.hpp>

namespace hamon
{

template <typename ForwardIterator>
inline void
uninitialized_value_construct(ForwardIterator first, ForwardIterator last)
{
	return hamon::detail::uninitialized_value_construct_impl(first, last);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_HPP
