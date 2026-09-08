/**
 *	@file	default_memory_resource.hpp
 *
 *	@brief	default_memory_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_DETAIL_DEFAULT_MEMORY_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_DETAIL_DEFAULT_MEMORY_RESOURCE_HPP

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/new_delete_resource.hpp>
#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/utility/exchange.hpp>

namespace hamon
{
namespace pmr
{
namespace detail
{

inline memory_resource* default_memory_resource(bool set, memory_resource* new_res) noexcept
{
	static memory_resource* res = hamon::pmr::new_delete_resource();
#if !defined(HAMON_NO_THREADS)
	static hamon::mutex mut;
#endif
	if (set)
	{
		if (new_res == nullptr)
		{
			new_res = hamon::pmr::new_delete_resource();
		}

#if !defined(HAMON_NO_THREADS)
		hamon::lock_guard<hamon::mutex> lk(mut);
#endif
		return hamon::exchange(res, new_res);
	}
	else
	{
#if !defined(HAMON_NO_THREADS)
		hamon::lock_guard<hamon::mutex> lk(mut);
#endif
		return res;
	}
}

}	// namespace detail
}	// namespace pmr
}	// namespace hamon

#endif // HAMON_MEMORY_RESOURCE_DETAIL_DEFAULT_MEMORY_RESOURCE_HPP
