/**
 *	@file	construct_at.hpp
 *
 *	@brief	construct_at の定義
 */

#ifndef HAMON_MEMORY_CONSTRUCT_AT_HPP
#define HAMON_MEMORY_CONSTRUCT_AT_HPP

#include <memory>

#if defined(__cpp_lib_constexpr_dynamic_alloc) && (__cpp_lib_constexpr_dynamic_alloc >= 201907)

namespace hamon
{

using std::construct_at;

}	// namespace hamon

#else

#include <utility>

namespace hamon
{

template <typename T, typename... Args>
inline auto
construct_at(T* p, Args&&... args)
noexcept(noexcept(::new(const_cast<void*>(static_cast<const volatile void*>(p))) T(std::forward<Args>(args)...)))
->decltype(::new(const_cast<void*>(static_cast<const volatile void*>(p))) T(std::forward<Args>(args)...))
{
	return ::new(const_cast<void*>(static_cast<const volatile void*>(p))) T(std::forward<Args>(args)...);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_CONSTRUCT_AT_HPP
