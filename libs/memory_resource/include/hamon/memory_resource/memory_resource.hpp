/**
 *	@file	memory_resource.hpp
 *
 *	@brief	memory_resource の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_MEMORY_RESOURCE_HPP
#define HAMON_MEMORY_RESOURCE_MEMORY_RESOURCE_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::memory_resource;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/bit/has_single_bit.hpp>
#include <hamon/cstddef/max_align_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace pmr
{

class memory_resource;

// 20.4.2 Class memory_resource[mem.res.class]

class memory_resource
{
	static constexpr hamon::size_t max_align = alignof(hamon::max_align_t);   // exposition only

public:
	memory_resource() = default;
	memory_resource(const memory_resource&) = default;

	virtual ~memory_resource()
	{
		// [mem.res.public]/1
	}

	memory_resource& operator=(const memory_resource&) = default;

	void* allocate(hamon::size_t bytes, hamon::size_t alignment = max_align)
	{
		// [mem.res.private]/1
		HAMON_ASSERT(hamon::has_single_bit(alignment));

		// [mem.res.public]/2,3
		return this->do_allocate(bytes, alignment);
	}

	void deallocate(void* p, hamon::size_t bytes, hamon::size_t alignment = max_align)
	{
		// [mem.res.public]/5
		this->do_deallocate(p, bytes, alignment);
	}

	bool is_equal(const memory_resource& other) const noexcept
	{
		// [mem.res.public]/6
		return this->do_is_equal(other);
	}

private:
	virtual void* do_allocate(hamon::size_t bytes, hamon::size_t alignment) = 0;

	virtual void do_deallocate(void* p, hamon::size_t bytes, hamon::size_t alignment) = 0;

	virtual bool do_is_equal(const memory_resource& other) const noexcept = 0;
};

inline bool
operator==(const memory_resource& a, const memory_resource& b) noexcept
{
	// [mem.res.eq]/1
	return &a == &b || a.is_equal(b);
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
inline bool
operator!=(const memory_resource& a, const memory_resource& b) noexcept
{
	return !(a == b);
}
#endif

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_MEMORY_RESOURCE_HPP
