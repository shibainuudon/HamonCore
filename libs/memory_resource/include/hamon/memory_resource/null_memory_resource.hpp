/**
 *	@file	null_memory_resource.hpp
 *
 *	@brief	null_memory_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_NULL_MEMORY_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_NULL_MEMORY_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::null_memory_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/new/bad_alloc.hpp>

namespace hamon
{
namespace pmr
{

namespace detail
{

class null_memory_resource_imp : public memory_resource
{
	void* do_allocate(hamon::size_t, hamon::size_t) override
	{
		hamon::detail::throw_bad_alloc();
	}

	void do_deallocate(void*, hamon::size_t, hamon::size_t) override
	{
	}

	bool do_is_equal(const memory_resource& other) const noexcept override
	{
		return this == &other;
	}
};

}	// namespace detail

inline memory_resource* null_memory_resource() noexcept
{
	static hamon::pmr::detail::null_memory_resource_imp res;
	return &res;
}

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_NULL_MEMORY_RESOURCE_HPP
