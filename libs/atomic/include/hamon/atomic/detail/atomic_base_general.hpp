/**
 *	@file	atomic_base_general.hpp
 *
 *	@brief	atomic_base_general の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP

#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/memory/addressof.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.1 General[atomics.types.generic.general]

template <typename T>
struct atomic_base_general
{
	using value_type = T;

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;

protected:
	constexpr atomic_base_general()
		: m_value()
	{}

	constexpr atomic_base_general(T desired)
		: m_value(desired)
	{}

	constexpr T* data() noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	constexpr T* data() const noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	constexpr T* data() volatile noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	constexpr T* data() const volatile noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

private:
	T m_value;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
