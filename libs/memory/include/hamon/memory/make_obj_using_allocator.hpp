/**
 *	@file	make_obj_using_allocator.hpp
 *
 *	@brief	make_obj_using_allocator の定義
 */

#ifndef HAMON_MEMORY_MAKE_OBJ_USING_ALLOCATOR_HPP
#define HAMON_MEMORY_MAKE_OBJ_USING_ALLOCATOR_HPP

#include <memory>

#if 0

namespace hamon
{

using std::make_obj_using_allocator;

}	// namespace hamon

#else

#include <hamon/memory/uses_allocator_construction_args.hpp>
#include <hamon/tuple/make_from_tuple.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename Alloc, typename... Args>
inline HAMON_CXX11_CONSTEXPR T
make_obj_using_allocator(Alloc const& alloc, Args&&... args)
{
	// [allocator.uses.construction]/23
	return hamon::make_from_tuple<T>(
		hamon::uses_allocator_construction_args<T>(
			alloc, hamon::forward<Args>(args)...));
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_MAKE_OBJ_USING_ALLOCATOR_HPP
