/**
 *	@file	atomic_wait.hpp
 *
 *	@brief	atomic_wait の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_WAIT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_WAIT_HPP

#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/memcmp_equal.hpp>
#include <hamon/atomic/detail/wait_on_address_native.hpp>
#include <hamon/atomic/detail/atomic_wait_state.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T, typename U, bool B = !hamon::detail::has_native_wait, typename = hamon::enable_if_t<B>>
void wait_on_address_impl(T*, T, U, hamon::detail::overload_priority<2>)
{
	// プラットフォーム固有のwait関数が無い場合:
	// この関数は何もしない、つまりatomic_waitはビジーループになる。
}

template <typename T, typename U, typename = hamon::enable_if_t<hamon::detail::is_native_waitable<T>::value>>
void wait_on_address_impl(T* ptr, T val, U, hamon::detail::overload_priority<1>)
{
	// 型Tでプラットフォーム固有のwait関数を呼び出し可能な場合:
	// 直接wait関数を呼び出す。
	hamon::detail::wait_on_address_native(ptr, val);
}

template <typename T, typename U>
void wait_on_address_impl(T* ptr, T val, U monitor, hamon::detail::overload_priority<0>)
{
	// 型Tでプラットフォーム固有のwait関数を呼び出し可能でない場合:
	// 呼び出し可能な型で間接的にwait関数を呼び出す。
	(void)val;
	auto entry = hamon::detail::get_atomic_wait_state(ptr);
	hamon::detail::wait_on_address_native(&entry->platform_state, monitor);
}

template <typename T, typename U>
HAMON_CXX14_CONSTEXPR void wait_on_address(T* ptr, T val, U monitor)
{
	if (hamon::is_constant_evaluated())
	{
		// do nothing
		return;
	}

	wait_on_address_impl(ptr, val, monitor, hamon::detail::overload_priority<2>{});
}

template <typename T, typename = hamon::enable_if_t<hamon::detail::is_native_waitable<T>::value>>
hamon::detail::native_wait_t atomic_wait_monitor_impl(T*, hamon::detail::overload_priority<1>)
{
	return 0;
}

template <typename T>
hamon::detail::native_wait_t atomic_wait_monitor_impl(T* ptr, hamon::detail::overload_priority<0>)
{
	auto entry = hamon::detail::get_atomic_wait_state(ptr);
	return hamon::detail::atomic_load(&entry->platform_state, hamon::memory_order::acquire);
}

template <typename T>
HAMON_CXX14_CONSTEXPR hamon::detail::native_wait_t atomic_wait_monitor(T* ptr)
{
	if (hamon::is_constant_evaluated())
	{
		return 0;
	}

	return atomic_wait_monitor_impl(ptr, hamon::detail::overload_priority<2>{});
}

template <typename T>
HAMON_CXX14_CONSTEXPR void atomic_wait(T* ptr, T old, hamon::memory_order order)
{
	auto monitor = atomic_wait_monitor(ptr);

	for (;;)
	{
		T current = hamon::detail::atomic_load(ptr, order);
		if (!hamon::detail::memcmp_equal(hamon::addressof(current), hamon::addressof(old)))
		{
			return;
		}

		wait_on_address(ptr, current, monitor);
	}
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_WAIT_HPP
