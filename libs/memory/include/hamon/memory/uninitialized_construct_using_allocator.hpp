/**
 *	@file	uninitialized_construct_using_allocator.hpp
 *
 *	@brief	uninitialized_construct_using_allocator の定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_CONSTRUCT_USING_ALLOCATOR_HPP
#define HAMON_MEMORY_UNINITIALIZED_CONSTRUCT_USING_ALLOCATOR_HPP

#include <memory>

#if 0

namespace hamon
{

using std::uninitialized_construct_using_allocator;

}	// namespace hamon

#else

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/uses_allocator_construction_args.hpp>
#include <hamon/tuple/apply.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace uses_allocator_detail
{

template <typename T>
struct ConstructAt
{
	template <typename... U>
	constexpr T* operator()(U&&... xs) const
	{
		return hamon::construct_at(m_p, hamon::forward<U>(xs)...);
	}

	T* m_p;
};

}	// namespace uses_allocator_detail

template <typename T, typename Alloc, typename... Args>
constexpr T* uninitialized_construct_using_allocator(T* p, const Alloc& alloc, Args&&... args)
{
	// [allocator.uses.construction]/24
	return hamon::apply(
		uses_allocator_detail::ConstructAt<T>{p},
		hamon::uses_allocator_construction_args<T>(alloc, hamon::forward<Args>(args)...)
	);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_CONSTRUCT_USING_ALLOCATOR_HPP
