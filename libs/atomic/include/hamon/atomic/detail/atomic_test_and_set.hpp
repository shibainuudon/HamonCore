/**
 *	@file	atomic_test_and_set.hpp
 *
 *	@brief	atomic_test_and_set の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_TEST_AND_SET_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_TEST_AND_SET_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

inline HAMON_CXX14_CONSTEXPR
bool atomic_test_and_set(bool* ptr, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		return hamon::exchange(*ptr, true);
	}

#if HAMON_HAS_BUILTIN(__atomic_test_and_set)
	return __atomic_test_and_set(ptr, hamon::detail::to_gcc_memory_order(order));
#else
	return hamon::detail::atomic_exchange(ptr, true, order);
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_TEST_AND_SET_HPP
