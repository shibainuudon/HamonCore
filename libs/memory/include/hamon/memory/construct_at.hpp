/**
 *	@file	construct_at.hpp
 *
 *	@brief	construct_at の定義
 */

#ifndef HAMON_MEMORY_CONSTRUCT_AT_HPP
#define HAMON_MEMORY_CONSTRUCT_AT_HPP

#include <memory>

#if defined(__cpp_lib_constexpr_dynamic_alloc) && (__cpp_lib_constexpr_dynamic_alloc >= 201907)

// construct_at が constexpr であることを定義
#define	HAMON_HAS_CONSTEXPR_CONSTRUCT_AT

namespace hamon
{

using std::construct_at;

}	// namespace hamon

#else

#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/detail/voidify.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

namespace detail
{

template <typename T, typename... Args,
	typename = hamon::enable_if_t<hamon::is_array<T>::value>>
HAMON_CXX14_CONSTEXPR T*
construct_at_impl(hamon::detail::overload_priority<2>, T* location, Args&&...)
HAMON_NOEXCEPT_IF_EXPR(::new (hamon::detail::voidify(*location)) T[1]())	// noexcept as an extension
{
	// [specialized.construct]/2
	static_assert(sizeof...(Args) == 0, "");

	// [specialized.construct]/3
	return ::new (hamon::detail::voidify(*location)) T[1]();
}

// Extension:
//  T が TriviallyMoveAssignable かつ TriviallyMoveConstructible かつ TriviallyDestructible なとき、
//  placement new を使わずに構築することで、C++14でもconstexprにできる。
template <typename T, typename... Args,
	typename = hamon::enable_if_t<
		hamon::is_trivially_move_assignable<T>::value &&
		hamon::is_trivially_move_constructible<T>::value &&
		hamon::is_trivially_destructible<T>::value>>
HAMON_CXX14_CONSTEXPR T*
construct_at_impl(hamon::detail::overload_priority<1>, T* location, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(T(hamon::forward<Args>(args)...))	// noexcept as an extension
{
	*location = T(hamon::forward<Args>(args)...);
	return location;
}

template <typename T, typename... Args>
HAMON_CXX14_CONSTEXPR T*
construct_at_impl(hamon::detail::overload_priority<0>, T* location, Args&&... args)
HAMON_NOEXCEPT_IF_EXPR(::new (hamon::detail::voidify(*location)) T(hamon::forward<Args>(args)...))	// noexcept as an extension
{
	// [specialized.construct]/3
	return ::new (hamon::detail::voidify(*location)) T(hamon::forward<Args>(args)...);
}

}	// namespace detail

// 26.11.8 construct_at[specialized.construct]

template <typename T, typename... Args,
	// [specialized.construct]/1
	typename = hamon::enable_if_t<!hamon::is_unbounded_array<T>::value>,
	typename = hamon::void_t<decltype(::new (hamon::declval<void*>()) T(hamon::declval<Args>()...))>>
HAMON_CXX14_CONSTEXPR T*
construct_at(T* location, Args&&... args) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
	hamon::detail::construct_at_impl(hamon::detail::overload_priority<2>{}, location, hamon::forward<Args>(args)...))
{
	return hamon::detail::construct_at_impl(hamon::detail::overload_priority<2>{}, location, hamon::forward<Args>(args)...);
}

}	// namespace hamon

HAMON_WARNING_POP()

#endif

#endif // HAMON_MEMORY_CONSTRUCT_AT_HPP
