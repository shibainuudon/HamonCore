/**
 *	@file	atomic.hpp
 *
 *	@brief	atomic の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_HPP
#define HAMON_ATOMIC_ATOMIC_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_base.hpp>

namespace hamon
{

// 32.5.8 Class template atomic[atomics.types.generic]

template <typename T>
struct atomic : public hamon::detail::atomic_base<T>
{
private:
	using base = hamon::detail::atomic_base<T>;

public:
	using base::base;
	using base::operator=;
};

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_HPP
