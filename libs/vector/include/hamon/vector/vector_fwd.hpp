/**
 *	@file	vector_fwd.hpp
 *
 *	@brief	vector の前方宣言
 */

#ifndef HAMON_VECTOR_VECTOR_FWD_HPP
#define HAMON_VECTOR_VECTOR_FWD_HPP

#include <hamon/vector/config.hpp>

#if defined(HAMON_USE_STD_VECTOR)

#include <vector>

namespace hamon
{

using std::vector;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

namespace hamon
{

template <typename T, typename Allocator = hamon::allocator<T>>
class vector;

}	// namespace hamon

#endif

#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon {
namespace pmr {

template <typename T>
using vector = hamon::vector<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_VECTOR_VECTOR_FWD_HPP
