/**
 *	@file	atomic_fetch_sub.hpp
 *
 *	@brief	atomic_fetch_sub の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_SUB_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_SUB_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/interlocked_exchange_add.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

// Note:
// gcc の __atomic_fetch_sub は浮動小数点数に対応していない(gcc-16 現在)
// SFINAEでテストしたかったが、引数の型違いの場合はハードエラーになってしまうようだ。
// (関数自体が無い場合はOK) 

// floating_point
#if HAMON_HAS_BUILTIN(__atomic_fetch_sub) && !defined(HAMON_GCC)
template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_CXX14_CONSTEXPR T
atomic_fetch_sub_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<2>)
{
	return __atomic_fetch_sub(ptr, val, hamon::detail::to_gcc_memory_order(order));
}
#endif

// integral
#if defined(HAMON_MSVC)
template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR T
atomic_fetch_sub_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<1>)
{
	(void)order;
	return hamon::detail::interlocked_exchange_add(ptr, static_cast<T>(~val + 1));
}
#elif HAMON_HAS_BUILTIN(__atomic_fetch_sub)
template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR T
atomic_fetch_sub_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<1>)
{
	return __atomic_fetch_sub(ptr, val, hamon::detail::to_gcc_memory_order(order));
}
#endif

// ビルトイン関数等が対応していない場合のジェネリックな実装
template <typename T>
HAMON_CXX14_CONSTEXPR T
atomic_fetch_sub_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<0>)
{
	auto oldval = hamon::detail::atomic_load(ptr, hamon::memory_order::relaxed);
	auto newval = oldval - val;
	while (!hamon::detail::atomic_compare_exchange_weak(
		ptr, hamon::addressof(oldval), newval, order, hamon::memory_order::relaxed))
	{
		newval = oldval - val;
	}
	return oldval;
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR T atomic_fetch_sub(T* ptr, T val, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		return hamon::exchange(*ptr, static_cast<T>(*ptr - val));
	}

	return hamon::detail::atomic_fetch_sub_impl(ptr, val, order, hamon::detail::overload_priority<2>{});
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR T atomic_fetch_sub(T* ptr, T val)
{
	return hamon::detail::atomic_fetch_sub(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_SUB_HPP
