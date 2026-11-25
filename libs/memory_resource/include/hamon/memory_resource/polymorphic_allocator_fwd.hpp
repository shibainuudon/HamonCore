/**
 *	@file	polymorphic_allocator_fwd.hpp
 *
 *	@brief	polymorphic_allocator の前方宣言
 */

#ifndef HAMON_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_FWD_HPP
#define HAMON_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_FWD_HPP

#include <hamon/cstddef/byte.hpp>

namespace hamon
{
namespace pmr
{

template <typename Tp = hamon::byte>
class polymorphic_allocator;

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_FWD_HPP
