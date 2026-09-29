/**
 *	@file	atomic_compare_exchange.hpp
 *
 *	@brief	atomic_compare_exchange の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_compare_exchange.hpp>
#include <hamon/atomic/detail/clear_padding_if_needed.hpp>
#include <hamon/cstring/memcmp.hpp>
#include <hamon/cstring/memcpy.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Watomic-alignment")

namespace hamon
{
namespace detail
{

// atomic_compare_exchangeでの比較はビット単位で行う。
// 例えば、floating-point type の +0.0 と -0.0 は区別される。
template <typename T, hamon::enable_if_t<!hamon::is_pointer_v<T>>* = nullptr>
HAMON_CXX14_CONSTEXPR bool mem_compare(T* lhs, T* rhs)
{
	return hamon::memcmp(lhs, rhs, sizeof(T)) == 0;
}

// Tがポインタ型の場合は以下の理由からmemcmpを使わない。
// ・異なるオブジェクトを指すポインタの大小比較を避けるため
// ・ポインタはbit_castできないため
template <typename T, hamon::enable_if_t<hamon::is_pointer_v<T>>* = nullptr>
HAMON_CXX14_CONSTEXPR bool mem_compare(T* lhs, T* rhs)
{
	return *lhs == *rhs;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool atomic_compare_exchange(T* ptr, T* expected, T desired, bool weak,
	hamon::memory_order success_memorder, hamon::memory_order failure_memorder)
{
	if (hamon::is_constant_evaluated())
	{
		if (hamon::detail::mem_compare(ptr, expected))
		{
			*ptr = desired;
			return true;
		}
		else
		{
			*expected = *ptr;
			return false;
		}
	}

	hamon::detail::clear_padding_if_needed(desired);
	T expected_copy = *expected;
	hamon::detail::clear_padding_if_needed(expected_copy);

#if defined(HAMON_MSVC)
	(void)weak;
	(void)success_memorder;
	(void)failure_memorder;
	*expected = hamon::detail::interlocked_compare_exchange(ptr, desired, expected_copy);
	return hamon::detail::mem_compare(&expected_copy, expected);
#else
	if (__atomic_compare_exchange(
		ptr, hamon::addressof(expected_copy), hamon::addressof(desired), weak,
		hamon::detail::to_gcc_memory_order(success_memorder),
		hamon::detail::to_gcc_memory_order(failure_memorder)))
	{
		return true;
	}
	else
	{
		hamon::memcpy(expected, hamon::addressof(expected_copy), sizeof(T));
		return false;
	}
#endif
}

}	// namespace detail
}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP
