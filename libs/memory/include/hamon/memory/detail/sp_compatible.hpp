/**
 *	@file	sp_compatible.hpp
 *
 *	@brief	sp_compatible を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SP_COMPATIBLE_HPP
#define HAMON_MEMORY_DETAIL_SP_COMPATIBLE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_convertible.hpp>

namespace hamon
{

namespace detail
{

// [util.smartptr.shared.general]
// For the purposes of [smartptr], a pointer type Y* is said to be compatible with
// a pointer type T* when either Y* is convertible to T* or Y is U[N] and T is cv U[].

template <typename Y, typename T>
struct sp_compatible : public hamon::is_convertible<Y*, T*>::type {};

template <typename U, hamon::size_t N> struct sp_compatible<U[N],                U[]> : public hamon::true_type {};
template <typename U, hamon::size_t N> struct sp_compatible<U[N], const          U[]> : public hamon::true_type {};
template <typename U, hamon::size_t N> struct sp_compatible<U[N],       volatile U[]> : public hamon::true_type {};
template <typename U, hamon::size_t N> struct sp_compatible<U[N], const volatile U[]> : public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SP_COMPATIBLE_HPP
