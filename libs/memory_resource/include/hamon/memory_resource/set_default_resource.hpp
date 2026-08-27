/**
 *	@file	set_default_resource.hpp
 *
 *	@brief	set_default_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_SET_DEFAULT_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_SET_DEFAULT_RESOURCE_HPP

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/detail/default_memory_resource.hpp>

namespace hamon
{
namespace pmr
{

inline memory_resource* set_default_resource(memory_resource* r) noexcept
{
	return hamon::pmr::detail::default_memory_resource(true, r);
}

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_MEMORY_RESOURCE_SET_DEFAULT_RESOURCE_HPP
