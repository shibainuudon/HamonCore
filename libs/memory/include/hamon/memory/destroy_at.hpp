/**
 *	@file	destroy_at.hpp
 *
 *	@brief	destroy_at の定義
 */

#ifndef HAMON_MEMORY_DESTROY_AT_HPP
#define HAMON_MEMORY_DESTROY_AT_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_constexpr_dynamic_alloc) && (__cpp_lib_constexpr_dynamic_alloc >= 201907) && \
	!(defined(HAMON_APPLE_CLANG))

namespace hamon
{

using std::destroy_at;

}	// namespace hamon

#else

#include <type_traits>

namespace hamon
{

template <typename T>
void destroy_at(T* p);

namespace detail
{

template <typename T>
inline void destroy_at_impl(T* p, std::false_type)
{
	p->~T();
}

template <typename T>
inline void destroy_at_impl(T* p, std::true_type)
{
	for (auto& x : *p)
	{
		hamon::destroy_at(std::addressof(x));
	}
}

}	// namespace detail

template <typename T>
inline void destroy_at(T* p)
{
	detail::destroy_at_impl(p, std::is_array<T>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_AT_HPP
