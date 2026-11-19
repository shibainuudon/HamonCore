/**
 *	@file	uses_allocator.hpp
 *
 *	@brief	uses_allocator の定義
 */

#ifndef HAMON_MEMORY_USES_ALLOCATOR_HPP
#define HAMON_MEMORY_USES_ALLOCATOR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Alloc, typename = void>
struct has_allocator_type
	: public hamon::false_type
{};

template <typename T, typename Alloc>
struct has_allocator_type<T, Alloc, hamon::void_t<typename T::allocator_type>>
    : public hamon::is_convertible<Alloc, typename T::allocator_type>
{};

}	// namespace detail

// [allocator.uses], uses_allocator
template <typename T, typename Alloc>
struct uses_allocator
	: public hamon::detail::has_allocator_type<T, Alloc>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

// [allocator.uses.trait], uses_allocator
template <typename T, typename Alloc>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool uses_allocator_v = uses_allocator<T, Alloc>::value;

#endif

}	// namespace hamon

#endif // HAMON_MEMORY_USES_ALLOCATOR_HPP
