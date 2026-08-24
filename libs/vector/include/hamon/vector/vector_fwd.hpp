/**
 *	@file	vector_fwd.hpp
 *
 *	@brief	vector の前方宣言
 */

#ifndef HAMON_VECTOR_VECTOR_FWD_HPP
#define HAMON_VECTOR_VECTOR_FWD_HPP

#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

template <typename T, typename Allocator = hamon::allocator<T>>
class vector;

namespace pmr {

template <typename T>
using vector = hamon::vector<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_VECTOR_VECTOR_FWD_HPP
