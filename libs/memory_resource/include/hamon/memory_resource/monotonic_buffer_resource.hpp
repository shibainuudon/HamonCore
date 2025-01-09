/**
 *	@file	monotonic_buffer_resource.hpp
 *
 *	@brief	monotonic_buffer_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_MONOTONIC_BUFFER_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_MONOTONIC_BUFFER_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::monotonic_buffer_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/algorithm/max.hpp>
#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uintptr_t.hpp>

namespace hamon
{
namespace pmr
{

class monotonic_buffer_resource : public memory_resource
{
	static const hamon::size_t default_buffer_capacity  = 1024;

	struct ChunkHeader
	{
		ChunkHeader*  next;
		hamon::size_t size;
	};

	struct Buffer
	{
		char* cur{};
		char* end{};
		hamon::size_t next_size{};

		void* try_allocate(hamon::size_t bytes, hamon::size_t align)
		{
			char* p = reinterpret_cast<char*>(hamon::round_up(reinterpret_cast<hamon::uintptr_t>(cur), align));
			if (p + bytes > end)
			{
				return nullptr;
			}
			cur = p + bytes;
			return p;
		}
	};

public:
	explicit monotonic_buffer_resource(memory_resource* upstream)
      : monotonic_buffer_resource(nullptr, default_buffer_capacity, upstream)
	{
		// [mem.res.monotonic.buffer.ctor]/1
		// [mem.res.monotonic.buffer.ctor]/2
	}

	monotonic_buffer_resource(hamon::size_t initial_size, memory_resource* upstream)
      : monotonic_buffer_resource(nullptr, initial_size, upstream)
	{
		// [mem.res.monotonic.buffer.ctor]/1
		// [mem.res.monotonic.buffer.ctor]/2
	}

	monotonic_buffer_resource(void* buffer, hamon::size_t buffer_size, memory_resource* upstream)
		: m_upstream_rsrc(upstream)
	{
		// [mem.res.monotonic.buffer.ctor]/3
		// [mem.res.monotonic.buffer.ctor]/4

		if (buffer != nullptr)
		{
			m_initial_buffer.cur  = static_cast<char*>(buffer);
			m_initial_buffer.end  = static_cast<char*>(buffer) + buffer_size;
			m_initial_buffer.next_size = buffer_size * 2;
		}
		else
		{
			m_initial_buffer.next_size = buffer_size;
		}

		m_current_buffer = m_initial_buffer;
	}

	monotonic_buffer_resource()
		: monotonic_buffer_resource(get_default_resource())
	{}

	explicit monotonic_buffer_resource(hamon::size_t initial_size)
		: monotonic_buffer_resource(initial_size, get_default_resource())
	{}

	monotonic_buffer_resource(void* buffer, hamon::size_t buffer_size)
		: monotonic_buffer_resource(buffer, buffer_size, get_default_resource())
	{}

	monotonic_buffer_resource(const monotonic_buffer_resource&) = delete;

	virtual ~monotonic_buffer_resource()
	{
		// [mem.res.monotonic.buffer.ctor]/5
		release();
	}

	monotonic_buffer_resource& operator=(const monotonic_buffer_resource&) = delete;

	void release()
	{
		// [mem.res.monotonic.buffer.mem]/1

		m_current_buffer = m_initial_buffer;

		while (m_chunk != nullptr)
		{
			auto next = m_chunk->next;
			m_upstream_rsrc->deallocate(m_chunk, m_chunk->size, alignof(ChunkHeader));
			m_chunk = next;
		}
	}

	memory_resource* upstream_resource() const
	{
		// [mem.res.monotonic.buffer.mem]/3
		return m_upstream_rsrc;
	}

protected:
	void* do_allocate(hamon::size_t bytes, hamon::size_t alignment) override
	{
		// [mem.res.monotonic.buffer.mem]/4
		// [mem.res.monotonic.buffer.mem]/5

		if (void* p = m_current_buffer.try_allocate(bytes, alignment))
		{
			return p;
		}

		hamon::size_t const chunk_size = hamon::max(bytes + alignment + sizeof(ChunkHeader), m_current_buffer.next_size);
		auto chunk_buffer = static_cast<char*>(m_upstream_rsrc->allocate(chunk_size, alignof(ChunkHeader)));
		auto chunk = hamon::construct_at(reinterpret_cast<ChunkHeader*>(chunk_buffer));
		chunk->size = chunk_size;
		chunk->next = m_chunk;
		m_chunk = chunk;

		m_current_buffer.cur = chunk_buffer + sizeof(ChunkHeader);
		m_current_buffer.end = chunk_buffer + chunk_size;
		m_current_buffer.next_size = chunk_size * 2;

		return m_current_buffer.try_allocate(bytes, alignment);
	}

	void do_deallocate(void* p, hamon::size_t bytes, hamon::size_t alignment) override
	{
		// [mem.res.monotonic.buffer.mem]/7
		// Do nothing.
		(void)p;
		(void)bytes;
		(void)alignment;
	}

	bool do_is_equal(const memory_resource& other) const noexcept override
	{
		// [mem.res.monotonic.buffer.mem]/10
		return this == &other;
	}

private:
	memory_resource* m_upstream_rsrc{};
	ChunkHeader* m_chunk{};
	Buffer m_initial_buffer{};
	Buffer m_current_buffer{};
};

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_MONOTONIC_BUFFER_RESOURCE_HPP
