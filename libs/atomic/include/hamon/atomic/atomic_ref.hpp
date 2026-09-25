/**
 *	@file	atomic_ref.hpp
 *
 *	@brief	atomic_ref の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_REF_HPP
#define HAMON_ATOMIC_ATOMIC_REF_HPP

#include <hamon/atomic/detail/atomic_ref_base.hpp>

namespace hamon
{

// 32.5.7 Class template atomic_ref[atomics.ref.generic]

template <typename T>
struct atomic_ref : public hamon::detail::atomic_ref_base<T>
{
private:
	using base = hamon::detail::atomic_ref_base<T>;

public:
	using base::base;
	using base::operator=;
};

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_REF_HPP
