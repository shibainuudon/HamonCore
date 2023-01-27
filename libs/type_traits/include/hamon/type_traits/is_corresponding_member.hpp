/**
 *	@file	is_corresponding_member.hpp
 *
 *	@brief	is_corresponding_member の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CORRESPONDING_MEMBER_HPP
#define HAMON_TYPE_TRAITS_IS_CORRESPONDING_MEMBER_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_is_layout_compatible) && (__cpp_lib_is_layout_compatible >= 201907)

using std::is_corresponding_member;

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__is_corresponding_member)

template <typename S1, typename S2, typename M1, typename M2>
constexpr bool
is_corresponding_member(M1 S1::*m1, M2 S2::*m2) noexcept
{
	return __is_corresponding_member(S1, S2, m1, m2);
}

#elif HAMON_HAS_BUILTIN(__builtin_is_corresponding_member)

template <typename S1, typename S2, typename M1, typename M2>
constexpr bool
is_corresponding_member(M1 S1::*m1, M2 S2::*m2) noexcept
{
	return __builtin_is_corresponding_member(m1, m2);
}

#else

#  define HAMON_NO_IS_CORRESPONDING_MEMBER

#endif

}	// namespace hamon

#if !defined(HAMON_NO_IS_CORRESPONDING_MEMBER)
#  define HAMON_HAS_IS_CORRESPONDING_MEMBER
#endif

#endif // HAMON_TYPE_TRAITS_IS_CORRESPONDING_MEMBER_HPP
