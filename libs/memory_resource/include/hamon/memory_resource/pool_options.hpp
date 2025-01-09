/**
 *	@file	pool_options.hpp
 *
 *	@brief	pool_options の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_POOL_OPTIONS_HPP
#define HAMON_MEMORY_RESOURCE_POOL_OPTIONS_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::pool_options;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{
namespace pmr
{

struct pool_options
{
	hamon::size_t max_blocks_per_chunk = 0;
	hamon::size_t largest_required_pool_block = 0;
};

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_POOL_OPTIONS_HPP
