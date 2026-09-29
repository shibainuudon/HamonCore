/**
 *	@file	atomic_base_general.hpp
 *
 *	@brief	atomic_base_general の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP

#include <hamon/atomic/detail/atomic_base_common.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.1 General[atomics.types.generic.general]

template <typename T>
struct atomic_base_general : public hamon::detail::atomic_base_common<T>
{
private:
	using base = hamon::detail::atomic_base_common<T>;
	using base::base;

public:
	using value_type = T;

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
