/**
 *	@file	atomic_notify_all.hpp
 *
 *	@brief	atomic_notify_all の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_NOTIFY_ALL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_NOTIFY_ALL_HPP

#include <hamon/atomic/detail/wait_on_address_native.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_wait_state.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T, bool B = !hamon::detail::has_native_wait, typename = hamon::enable_if_t<B>>
void wake_by_address_all(T*, hamon::detail::overload_priority<2>)
{
	// do nothing
}

template <typename T, typename = hamon::enable_if_t<hamon::detail::is_native_waitable<T>::value>>
void wake_by_address_all(T* ptr, hamon::detail::overload_priority<1>)
{
	hamon::detail::wake_by_address_all_native(ptr);
}

template <typename T>
void wake_by_address_all(T* ptr, hamon::detail::overload_priority<0>)
{
	auto entry = hamon::detail::get_atomic_wait_state(ptr);
	hamon::detail::atomic_fetch_add(&entry->platform_state, 1, hamon::memory_order::seq_cst);
	hamon::detail::wake_by_address_all_native(&entry->platform_state);
}

template <typename T>
HAMON_CXX14_CONSTEXPR void atomic_notify_all(T* ptr)
{
	if (hamon::is_constant_evaluated())
	{
		// do nothing
		return;
	}

	wake_by_address_all(ptr, hamon::detail::overload_priority<2>{});
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_NOTIFY_ALL_HPP
