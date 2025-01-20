/**
 *	@file	start_lifetime_as.hpp
 *
 *	@brief	start_lifetime_as の定義
 */

#ifndef HAMON_MEMORY_START_LIFETIME_AS_HPP
#define HAMON_MEMORY_START_LIFETIME_AS_HPP

#include <memory>

#if defined(__cpp_lib_start_lifetime_as) && (__cpp_lib_start_lifetime_as >= 202207L)

namespace hamon
{

using std::start_lifetime_as;

}	// namespace hamon

#else

#include <hamon/new/launder.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/is_implicit_lifetime.hpp>
#include <cstring>

namespace hamon
{

template <typename T,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_trivially_copyable<T>, hamon::is_implicit_lifetime<T>
	>::value>>
//requires (hamon::is_trivially_copyable_v<T> && hamon::is_implicit_lifetime_v<T>)
T* start_lifetime_as(void* p) noexcept
{
#if defined(HAMON_HAS_LAUNDER)
	return hamon::launder(static_cast<T*>(std::memmove(p, p, sizeof(T))));
#else
	return static_cast<T*>(std::memmove(p, p, sizeof(T)));
#endif
}

template <typename T,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_trivially_copyable<T>, hamon::is_implicit_lifetime<T>
	>::value>>
//requires (hamon::is_trivially_copyable_v<T> && hamon::is_implicit_lifetime_v<T>)
T const* start_lifetime_as(void const* p) noexcept
{
#if defined(HAMON_HAS_LAUNDER)
	return hamon::launder(static_cast<T const*>(std::memmove(const_cast<void*>(p), p, sizeof(T))));
#else
	return static_cast<T const*>(std::memmove(const_cast<void*>(p), p, sizeof(T)));
#endif
}

template <typename T,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_trivially_copyable<T>, hamon::is_implicit_lifetime<T>
	>::value>>
//requires (hamon::is_trivially_copyable_v<T> && hamon::is_implicit_lifetime_v<T>)
T volatile* start_lifetime_as(void volatile* p) noexcept
{
#if defined(HAMON_HAS_LAUNDER)
	return hamon::launder(static_cast<T volatile*>(std::memmove(const_cast<void*>(p), const_cast<void const*>(p), sizeof(T))));
#else
	return static_cast<T volatile*>(std::memmove(const_cast<void*>(p), const_cast<void const*>(p), sizeof(T)));
#endif
}

template <typename T,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::is_trivially_copyable<T>, hamon::is_implicit_lifetime<T>
	>::value>>
//requires (hamon::is_trivially_copyable_v<T> && hamon::is_implicit_lifetime_v<T>)
T const volatile* start_lifetime_as(void const volatile* p) noexcept
{
#if defined(HAMON_HAS_LAUNDER)
	return hamon::launder(static_cast<T const volatile*>(std::memmove(const_cast<void*>(p), const_cast<void const*>(p), sizeof(T))));
#else
	return static_cast<T const volatile*>(std::memmove(const_cast<void*>(p), const_cast<void const*>(p), sizeof(T)));
#endif
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_START_LIFETIME_AS_HPP
