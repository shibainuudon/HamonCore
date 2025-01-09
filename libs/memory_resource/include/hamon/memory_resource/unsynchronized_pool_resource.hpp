/**
 *	@file	unsynchronized_pool_resource.hpp
 *
 *	@brief	unsynchronized_pool_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_UNSYNCHRONIZED_POOL_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_UNSYNCHRONIZED_POOL_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::unsynchronized_pool_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/pool_options.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/algorithm/clamp.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/bit/bit_ceil.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace pmr
{

class unsynchronized_pool_resource : public memory_resource
{
private:
	struct Upstream
	{
		struct ChunkHeader
		{
			ChunkHeader*  next;
			char*         start;
			hamon::size_t size;
		};

		memory_resource* m_resource{};
		ChunkHeader*     m_chunk{};

		Upstream(memory_resource* resource)
			: m_resource(resource)
		{}

		void* allocate(hamon::size_t bytes, hamon::size_t alignment)
		{
			hamon::size_t const chunk_size = bytes + alignment + sizeof(ChunkHeader);
			auto chunk_buffer = static_cast<char*>(m_resource->allocate(chunk_size, alignof(ChunkHeader)));
			auto chunk = reinterpret_cast<ChunkHeader*>(chunk_buffer);
			chunk->size = chunk_size;
			chunk->next = m_chunk;
			m_chunk = chunk;

			auto p = chunk_buffer + sizeof(ChunkHeader);
			p = reinterpret_cast<char*>(hamon::round_up(reinterpret_cast<hamon::uintptr_t>(p), alignment));
			chunk->start = p;

			return p;
		}

		void deallocate(void* p, hamon::size_t bytes, hamon::size_t alignment)
		{
			(void)bytes;
			(void)alignment;

			ChunkHeader* prev = nullptr;
			auto chunk = m_chunk;
			while (chunk != nullptr)
			{
				if (chunk->start == p)
				{
					if (prev == nullptr)
					{
						m_chunk = chunk->next;
					}
					else
					{
						prev->next = chunk->next;
					}

					m_resource->deallocate(chunk, chunk->size, alignof(ChunkHeader));
					return;
				}
				prev = chunk;
				chunk = chunk->next;
			}
		}

		void release()
		{
			while (m_chunk != nullptr)
			{
				auto next = m_chunk->next;
				m_resource->deallocate(m_chunk, m_chunk->size, alignof(ChunkHeader));
				m_chunk = next;
			}
		}
	};

	struct FixedPool
	{
		struct FreeBlock
		{
			FreeBlock* next;
		};

		FreeBlock*	m_free_block{};
		hamon::size_t m_block_bytes;
		hamon::size_t m_block_num;

		FixedPool(hamon::size_t block_bytes)
			: m_block_bytes(block_bytes)
			, m_block_num(128)	// TODO
		{}

		void* try_allocate()
		{
			if (m_free_block == nullptr)
			{
				return nullptr;
			}

			void* p = m_free_block;
			m_free_block = m_free_block->next;
			return p;
		}

		void deallocate(void* p)
		{
			auto block = reinterpret_cast<FreeBlock*>(p);
			block->next = m_free_block;
			m_free_block = block;
		}

		void expand(Upstream* upstream, hamon::size_t max_blocks_per_chunk)
		{
			auto p = reinterpret_cast<char*>(upstream->allocate(m_block_bytes * m_block_num, alignof(FreeBlock)));
			for (hamon::size_t i = 0; i < m_block_num; ++i)
			{
				auto cur = reinterpret_cast<FreeBlock*>(p + i * m_block_bytes);
				if (i + 1 < m_block_num)
				{
					auto next = reinterpret_cast<FreeBlock*>(p + (i + 1) * m_block_bytes);
					cur->next = next;
				}
				else
				{
					cur->next = nullptr;
				}
			}

			m_free_block = reinterpret_cast<FreeBlock*>(p);

			m_block_num = hamon::min(m_block_num + m_block_num / 2, max_blocks_per_chunk);
		}
	};

	static hamon::size_t calc_pool_index(hamon::size_t bytes, hamon::size_t align)
	{
		if (align > alignof(hamon::max_align_t))
		{
			return hamon::numeric_limits<hamon::size_t>::max();
		}

		bytes = hamon::round_up(bytes, align);
		return static_cast<hamon::size_t>(hamon::countr_zero(hamon::bit_ceil(bytes)));
	}

public:
	unsynchronized_pool_resource(const pool_options& opts, memory_resource* upstream)
		: m_upstream(upstream)
	{
		// [mem.res.pool.ctor]/1
		// [mem.res.pool.ctor]/2
		// [mem.res.pool.ctor]/3

		static const hamon::size_t max_blocks_per_chunk_min     = 16;
		static const hamon::size_t max_blocks_per_chunk_max     = (hamon::size_t(1) << 20);
		static const hamon::size_t max_blocks_per_chunk_default = (hamon::size_t(1) << 20);

		static const hamon::size_t largest_block_size_min     = 8;
		static const hamon::size_t largest_block_size_max     = (hamon::size_t(1) << 30);
		static const hamon::size_t largest_block_size_default = (hamon::size_t(1) << 20);

		if (opts.max_blocks_per_chunk == 0)
		{
			m_options.max_blocks_per_chunk = max_blocks_per_chunk_default;
		}
		else
		{
			m_options.max_blocks_per_chunk = hamon::clamp(
				opts.max_blocks_per_chunk,
				max_blocks_per_chunk_min,
				max_blocks_per_chunk_max);
		}

		if (opts.largest_required_pool_block == 0)
		{
			m_options.largest_required_pool_block = largest_block_size_default;
		}
		else
		{
			m_options.largest_required_pool_block = hamon::clamp(
				opts.largest_required_pool_block,
				largest_block_size_min,
				largest_block_size_max);
		}

		m_fixed_pools_num = calc_pool_index(m_options.largest_required_pool_block, alignof(FixedPool));
	}

	unsynchronized_pool_resource()
		: unsynchronized_pool_resource(pool_options(), get_default_resource())
	{}

	explicit unsynchronized_pool_resource(memory_resource* upstream)
		: unsynchronized_pool_resource(pool_options(), upstream)
	{}

	explicit unsynchronized_pool_resource(const pool_options& opts)
		: unsynchronized_pool_resource(opts, get_default_resource())
	{}

	unsynchronized_pool_resource(const unsynchronized_pool_resource&) = delete;

	virtual ~unsynchronized_pool_resource()
	{
		// [mem.res.pool.ctor]/4
		release();
	}

	unsynchronized_pool_resource& operator=(const unsynchronized_pool_resource&) = delete;

	void release()
	{
		// [mem.res.pool.mem]/1

		m_upstream.release();

		upstream_resource()->deallocate(
			m_fixed_pools, m_fixed_pools_num * sizeof(FixedPool), alignof(FixedPool));
		m_fixed_pools = nullptr;
	}

	memory_resource* upstream_resource() const
	{
		// [mem.res.pool.mem]/2
		return m_upstream.m_resource;
	}

	pool_options options() const
	{
		// [mem.res.pool.mem]/3
		return m_options;
	}

protected:
	void* do_allocate(hamon::size_t bytes, hamon::size_t alignment) override
	{
		// [mem.res.pool.mem]/4
		// [mem.res.pool.mem]/5
		// [mem.res.pool.mem]/6

		auto const index = calc_pool_index(bytes, alignment);

		if (index >= m_fixed_pools_num)
		{
			return m_upstream.allocate(bytes, alignment);
		}

		if (m_fixed_pools == nullptr)
		{
			m_fixed_pools = reinterpret_cast<FixedPool*>(
				upstream_resource()->allocate(m_fixed_pools_num * sizeof(FixedPool), alignof(FixedPool)));

			for (hamon::size_t i = 0; i < m_fixed_pools_num; ++i)
			{
				hamon::construct_at(&m_fixed_pools[i], hamon::size_t(1) << i);
			}
		}

		HAMON_ASSERT(m_fixed_pools != nullptr);
		HAMON_ASSERT(bytes <= m_fixed_pools[index].m_block_bytes);

		if (void* p = m_fixed_pools[index].try_allocate())
		{
			return p;
		}

		m_fixed_pools[index].expand(&m_upstream, m_options.max_blocks_per_chunk);

		return m_fixed_pools[index].try_allocate();
	}

	void do_deallocate(void* p, hamon::size_t bytes, hamon::size_t alignment) override
	{
		// [mem.res.pool.mem]/7

		auto const index = calc_pool_index(bytes, alignment);

		if (index >= m_fixed_pools_num)
		{
			m_upstream.deallocate(p, bytes, alignment);
			return;
		}

		HAMON_ASSERT(m_fixed_pools != nullptr);

		m_fixed_pools[index].deallocate(p);
	}

	bool do_is_equal(const memory_resource& other) const noexcept override
	{
		// [mem.res.pool.mem]/9
		return this == &other;
	}

private:
	Upstream         m_upstream;
	pool_options     m_options{};
	FixedPool*       m_fixed_pools{};
	hamon::size_t    m_fixed_pools_num{};
};

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_UNSYNCHRONIZED_POOL_RESOURCE_HPP
