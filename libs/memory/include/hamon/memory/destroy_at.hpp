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
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/detail/overload_priority.hpp>

namespace hamon
{

template <typename T>
HAMON_CXX14_CONSTEXPR void destroy_at(T* p);

namespace detail
{

template <typename T,
	bool = hamon::is_array<T>::value,
	bool = hamon::is_trivially_destructible<T>::value
>
struct destroy_at_impl;

template <typename T, bool B>
struct destroy_at_impl<T, true, B>
{
	static HAMON_CXX14_CONSTEXPR void
	invoke(T* p)
	{
		for (auto& x : *p)
		{
			hamon::destroy_at(hamon::addressof(x));
		}
	}
};

template <typename T>
struct destroy_at_impl<T, false, false>
{
	static HAMON_CXX20_CONSTEXPR void
	invoke(T* p)
	{
		p->~T();
	}
};

template <typename T>
struct destroy_at_impl<T, false, true>
{
	static HAMON_CXX14_CONSTEXPR void
	invoke(T*)
	{
		// do nothing
	}
};

}	// namespace detail

// 27.11.9 destroy[specialized.destroy]

template <typename T>
HAMON_CXX14_CONSTEXPR void
destroy_at(T* p)
{
	hamon::detail::destroy_at_impl<T>::invoke(p);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_DESTROY_AT_HPP
