/**
 *	@file	atomic_store_add.hpp
 *
 *	@brief	atomic_store_add の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_STORE_ADD_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_STORE_ADD_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/interlocked_exchange_add.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T, typename = void>
struct has_builtin_atomic_store_add
	: public hamon::false_type
{};

template <typename T>
struct has_builtin_atomic_store_add<T, hamon::void_t<decltype(__atomic_store_add(hamon::declval<T*>(), hamon::declval<T>(), 0))>>
	: public hamon::true_type
{};

template <typename T, typename = hamon::enable_if_t<has_builtin_atomic_store_add<T>::value>>
HAMON_CXX14_CONSTEXPR void
atomic_store_add_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<2>)
{
	__atomic_store_add(ptr, val, hamon::detail::to_gcc_memory_order(order));
}

#if defined(HAMON_MSVC)
template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR void
atomic_store_add_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<1>)
{
	(void)order;
	// TODO: win32で__atomic_store_addに相当するような効率の良い処理があるかどうか未確認
	hamon::detail::interlocked_exchange_add(ptr, val);
}
#endif

template <typename T>
HAMON_CXX14_CONSTEXPR void
atomic_store_add_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<0>)
{
	// TODO: __atomic_store_addビルトイン関数が実装されるまでは atomic_fetch_add で代用する
	hamon::detail::atomic_fetch_add(ptr, val, order);
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_add(T* ptr, T val, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		hamon::exchange(*ptr, static_cast<T>(*ptr + val));
		return;
	}

	hamon::detail::atomic_store_add_impl(ptr, val, order, hamon::detail::overload_priority<2>{});
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_add(T* ptr, T val)
{
	hamon::detail::atomic_store_add(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_STORE_ADD_HPP
