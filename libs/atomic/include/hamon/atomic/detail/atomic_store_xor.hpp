/**
 *	@file	atomic_store_xor.hpp
 *
 *	@brief	atomic_store_xor の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_STORE_XOR_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_STORE_XOR_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_xor.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_xor(T* ptr, T val, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		hamon::exchange(*ptr, static_cast<T>(*ptr ^ val));
		return;
	}

#if defined(HAMON_MSVC)
	(void)order;
	// TODO: win32で__atomic_store_xorに相当するような効率の良い処理があるかどうか未確認
	hamon::detail::interlocked_xor(ptr, val);
#else
	// TODO: __atomic_store_xorビルトイン関数が実装されるまでは__atomic_fetch_xorで代用する
	__atomic_fetch_xor(ptr, val, hamon::detail::to_gcc_memory_order(order));
#endif
}

template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_xor(T* ptr, T val)
{
	hamon::detail::atomic_store_xor(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_STORE_XOR_HPP
