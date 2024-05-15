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

#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/detail/overload_priority.hpp>

namespace hamon
{

template <typename T>
HAMON_CXX20_CONSTEXPR void destroy_at(T* p);

namespace detail
{

template <typename T, typename = hamon::enable_if_t<hamon::is_array<T>::value>>
HAMON_CXX20_CONSTEXPR void
destroy_at_impl(T* p, hamon::detail::overload_priority<1>)
{
	for (auto& x : *p)
	{
		hamon::destroy_at(hamon::addressof(x));
	}
}

template <typename T>
HAMON_CXX20_CONSTEXPR void
destroy_at_impl(T* p, hamon::detail::overload_priority<0>)
{
	p->~T();
}

}	// namespace detail

template <typename T>
HAMON_CXX20_CONSTEXPR void
destroy_at(T* p)
{
	hamon::detail::destroy_at_impl(p, hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_AT_HPP
