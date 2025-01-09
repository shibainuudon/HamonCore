/**
 *	@file	new_delete_resource.hpp
 *
 *	@brief	new_delete_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_NEW_DELETE_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_NEW_DELETE_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::new_delete_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdlib/aligned_alloc.hpp>

namespace hamon
{
namespace pmr
{

namespace detail
{

class new_delete_memory_resource_imp : public memory_resource
{
	void* do_allocate(hamon::size_t bytes, hamon::size_t align) override
	{
		return hamon::aligned_alloc(align, bytes);
	}

	void do_deallocate(void* p, hamon::size_t bytes, hamon::size_t align) override
	{
		(void)bytes;
		(void)align;
		hamon::aligned_free(p);
	}

	bool do_is_equal(const memory_resource& other) const noexcept override
	{
		return this == &other;
	}
};

}	// namespace detail

inline memory_resource* new_delete_resource() noexcept
{
	static hamon::pmr::detail::new_delete_memory_resource_imp res;
	return &res;
}

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_NEW_DELETE_RESOURCE_HPP
