/**
 *	@file	synchronized_pool_resource.hpp
 *
 *	@brief	synchronized_pool_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_SYNCHRONIZED_POOL_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_SYNCHRONIZED_POOL_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::synchronized_pool_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/pool_options.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory_resource/unsynchronized_pool_resource.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <mutex>

namespace hamon
{
namespace pmr
{

class synchronized_pool_resource : public memory_resource
{
public:
	synchronized_pool_resource(const pool_options& opts, memory_resource* upstream)
		: m_unsync(opts, upstream)
	{}

	synchronized_pool_resource()
		: synchronized_pool_resource(pool_options(), get_default_resource())
	{}

	explicit synchronized_pool_resource(memory_resource* upstream)
		: synchronized_pool_resource(pool_options(), upstream)
	{}

	explicit synchronized_pool_resource(const pool_options& opts)
		: synchronized_pool_resource(opts, get_default_resource())
	{}

	synchronized_pool_resource(const synchronized_pool_resource&) = delete;

	virtual ~synchronized_pool_resource()
	{
		// [mem.res.pool.ctor]/4
		release();
	}

	synchronized_pool_resource& operator=(const synchronized_pool_resource&) = delete;

	void release()
	{
#if !defined(HAMON_NO_THREADS)
		std::lock_guard<std::mutex> lk(m_mut);
#endif
		m_unsync.release();
	}

	memory_resource* upstream_resource() const
	{
		return m_unsync.upstream_resource();
	}

	pool_options options() const
	{
		return m_unsync.options();
	}

protected:
	void* do_allocate(hamon::size_t bytes, hamon::size_t alignment) override
	{
#if !defined(HAMON_NO_THREADS)
		std::lock_guard<std::mutex> lk(m_mut);
#endif
		return m_unsync.allocate(bytes, alignment);
	}

	void do_deallocate(void* p, hamon::size_t bytes, hamon::size_t alignment) override
	{
#if !defined(HAMON_NO_THREADS)
		std::lock_guard<std::mutex> lk(m_mut);
#endif
		return m_unsync.deallocate(p, bytes, alignment);
	}

	bool do_is_equal(const memory_resource& other) const noexcept override
	{
		// [mem.res.pool.mem]/9
		return this == &other;
	}

private:
#if !defined(HAMON_NO_THREADS)
	std::mutex m_mut;
#endif
	unsynchronized_pool_resource	m_unsync;
};

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_SYNCHRONIZED_POOL_RESOURCE_HPP
