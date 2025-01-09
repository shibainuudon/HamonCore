/**
 *	@file	get_default_resource.hpp
 *
 *	@brief	get_default_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_GET_DEFAULT_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_GET_DEFAULT_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::get_default_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/detail/default_memory_resource.hpp>

namespace hamon
{
namespace pmr
{

inline memory_resource* get_default_resource() noexcept
{
	return hamon::pmr::detail::default_memory_resource(false, nullptr);
}

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_GET_DEFAULT_RESOURCE_HPP
