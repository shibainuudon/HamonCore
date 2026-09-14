/**
 *	@file	atomic_fetch_fmaximum_num.hpp
 *
 *	@brief	atomic_fetch_fmaximum_num の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_FMAXIMUM_NUM_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_FMAXIMUM_NUM_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/cmath/fmaximum_num.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/addressof.hpp>
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
struct has_builtin_atomic_fetch_fmaximum_num
	: public hamon::false_type
{};

template <typename T>
struct has_builtin_atomic_fetch_fmaximum_num<T, hamon::void_t<decltype(__atomic_fetch_fmaximum_num(hamon::declval<T*>(), hamon::declval<T>(), 0))>>
	: public hamon::true_type
{};

template <typename T, typename = hamon::enable_if_t<has_builtin_atomic_fetch_fmaximum_num<T>::value>>
HAMON_CXX14_CONSTEXPR T
atomic_fetch_fmaximum_num_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<2>)
{
	return __atomic_fetch_fmaximum_num(ptr, val, hamon::detail::to_gcc_memory_order(order));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
atomic_fetch_fmaximum_num_impl(T* ptr, T val, hamon::memory_order order, hamon::detail::overload_priority<0>)
{
	T ret = hamon::detail::atomic_load(ptr, hamon::memory_order::relaxed);
	T value{};
	do
	{
		value = hamon::fmaximum_num(ret, val);
	}
	while (!hamon::detail::atomic_compare_exchange_weak(
		ptr, hamon::addressof(ret), value, order, hamon::memory_order::relaxed));

	return ret;
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR T atomic_fetch_fmaximum_num(T* ptr, T val, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		return hamon::exchange(*ptr, hamon::fmaximum_num(*ptr, val));
	}

	return hamon::detail::atomic_fetch_fmaximum_num_impl(ptr, val, order, hamon::detail::overload_priority<2>{});
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR T atomic_fetch_fmaximum_num(T* ptr, T val)
{
	return hamon::detail::atomic_fetch_fmaximum_num(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_FMAXIMUM_NUM_HPP
