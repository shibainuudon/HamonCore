/**
 *	@file	polymorphic_allocator.hpp
 *
 *	@brief	polymorphic_allocator の定義
 */

#ifndef HAMON_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_HPP
#define HAMON_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_HPP

#include <hamon/memory_resource/config.hpp>

#if defined(HAMON_USE_STD_MEMORY_RESOURCE)

#include <memory_resource>

namespace hamon
{
namespace pmr
{

using std::pmr::polymorphic_allocator;

}	// namespace pmr
}	// namespace hamon

#else

#include <hamon/memory_resource/memory_resource.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory/uninitialized_construct_using_allocator.hpp>
#include <hamon/cstddef/byte.hpp>
#include <hamon/cstddef/max_align_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/new/bad_array_new_length.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace pmr
{

// 20.4.3 Class template polymorphic_allocator[mem.poly.allocator.class]

template <typename Tp = hamon::byte>
class polymorphic_allocator
{
	memory_resource* memory_rsrc;       // exposition only

public:
	using value_type = Tp;

	// [mem.poly.allocator.ctor], constructors
	polymorphic_allocator() noexcept
		: memory_rsrc(get_default_resource())	// [mem.poly.allocator.ctor]/1
	{}

	polymorphic_allocator(memory_resource* r)
		: memory_rsrc(r)	// [mem.poly.allocator.ctor]/3
	{
		HAMON_ASSERT(r != nullptr);	// [mem.poly.allocator.ctor]/2
	}

	polymorphic_allocator(const polymorphic_allocator& other) = default;

	template <typename U>
	polymorphic_allocator(const polymorphic_allocator<U>& other) noexcept
		: memory_rsrc(other.resource())	// [mem.poly.allocator.ctor]/6
	{}

	polymorphic_allocator& operator=(const polymorphic_allocator&) = delete;

	// [mem.poly.allocator.mem], member functions
	Tp* allocate(hamon::size_t n)
	{
		// [mem.poly.allocator.mem]/1
		if (hamon::numeric_limits<hamon::size_t>::max() / sizeof(Tp) < n)
		{
			hamon::detail::throw_bad_array_new_length();
		}

		return static_cast<Tp*>(memory_rsrc->allocate(n * sizeof(Tp), alignof(Tp)));
	}

	void deallocate(Tp* p, hamon::size_t n)
	{
		// [mem.poly.allocator.mem]/3
		memory_rsrc->deallocate(p, n * sizeof(Tp), alignof(Tp));
	}

	void* allocate_bytes(hamon::size_t nbytes, hamon::size_t alignment = alignof(hamon::max_align_t))
	{
		// [mem.poly.allocator.mem]/5
		return memory_rsrc->allocate(nbytes, alignment);
	}

	void deallocate_bytes(void* p, hamon::size_t nbytes, hamon::size_t alignment = alignof(hamon::max_align_t))
	{
		// [mem.poly.allocator.mem]/7
		memory_rsrc->deallocate(p, nbytes, alignment);
	}

	template <typename T>
	T* allocate_object(hamon::size_t n = 1)
	{
		if (hamon::numeric_limits<hamon::size_t>::max() / sizeof(T) < n)
		{
			// [mem.poly.allocator.mem]/8.1
			hamon::detail::throw_bad_array_new_length();
		}

		// [mem.poly.allocator.mem]/8.2
		return static_cast<T*>(allocate_bytes(n*sizeof(T), alignof(T)));
	}

	template <typename T>
	void deallocate_object(T* p, hamon::size_t n = 1)
	{
		// [mem.poly.allocator.mem]/10
		deallocate_bytes(p, n*sizeof(T), alignof(T));
	}

	template <typename T, typename... CtorArgs>
	T* new_object(CtorArgs&&... ctor_args)
	{
		// [mem.poly.allocator.mem]/11
		T* p = allocate_object<T>();
#if !defined(HAMON_NO_EXCEPTIONS)
		try
#endif
		{
			construct(p, hamon::forward<CtorArgs>(ctor_args)...);
		}
#if !defined(HAMON_NO_EXCEPTIONS)
		catch (...)
		{
			deallocate_object(p);
			throw;
		}
#endif

		return p;
	}

	template <typename T>
	void delete_object(T* p)
	{
		// [mem.poly.allocator.mem]/13
		destroy(p);
		deallocate_object(p);
	}

	template <typename T, typename... Args>
	void construct(T* p, Args&&... args)
	{
		// [mem.poly.allocator.mem]/15
		hamon::uninitialized_construct_using_allocator(
			p, *this, hamon::forward<Args>(args)...);
	}

	template <typename T>
	void destroy(T* p)
	{
		// [mem.poly.allocator.mem]/17
		p->~T();
	}

	polymorphic_allocator select_on_container_copy_construction() const
	{
		// [mem.poly.allocator.mem]/18
		return polymorphic_allocator();
	}

	memory_resource* resource() const
	{
		// [mem.poly.allocator.mem]/20
		return memory_rsrc;
	}

	// friends
	friend bool operator==(
		const polymorphic_allocator& a,
		const polymorphic_allocator& b) noexcept
	{
		return *a.resource() == *b.resource();
	}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend bool operator!=(
		const polymorphic_allocator& a,
		const polymorphic_allocator& b) noexcept
	{
		return !(a == b);
	}
#endif
};

template <typename T1, typename T2>
bool operator==(
	const polymorphic_allocator<T1>& a,
	const polymorphic_allocator<T2>& b) noexcept
{
	// [mem.poly.allocator.eq]/1
	return *a.resource() == *b.resource();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T1, typename T2>
bool operator!=(
	const polymorphic_allocator<T1>& a,
	const polymorphic_allocator<T2>& b) noexcept
{
	return !(a == b);
}
#endif

}	// namespace pmr
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RESOURCE_POLYMORPHIC_ALLOCATOR_HPP
