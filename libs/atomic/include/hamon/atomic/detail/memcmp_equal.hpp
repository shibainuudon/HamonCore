/**
 *	@file	memcmp_equal.hpp
 *
 *	@brief	memcmp_equal の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_MEMCMP_EQUAL_HPP
#define HAMON_ATOMIC_DETAIL_MEMCMP_EQUAL_HPP

#include <hamon/cstring/memcmp.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

// ビット単位での比較を行う。
// 例えば、floating-point type の +0.0 と -0.0 は区別される。
template <typename T, hamon::enable_if_t<!hamon::is_pointer_v<T>>* = nullptr>
HAMON_CXX14_CONSTEXPR bool memcmp_equal(T const* lhs, T const* rhs)
{
	return hamon::memcmp(lhs, rhs, sizeof(T)) == 0;
}

// Tがポインタ型の場合は以下の理由からmemcmpを使わない。
// ・異なるオブジェクトを指すポインタの大小比較を避けるため
// ・ポインタはbit_castできないため
template <typename T, hamon::enable_if_t<hamon::is_pointer_v<T>>* = nullptr>
HAMON_CXX14_CONSTEXPR bool memcmp_equal(T const* lhs, T const* rhs)
{
	return *lhs == *rhs;
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_MEMCMP_EQUAL_HPP
