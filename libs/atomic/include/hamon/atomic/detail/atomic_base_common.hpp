/**
 *	@file	atomic_base_common.hpp
 *
 *	@brief	atomic_base_common の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_COMMON_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_COMMON_HPP

#include <hamon/atomic/detail/clear_padding_if_needed.hpp>
#include <hamon/memory/addressof.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
struct atomic_base_common
{
protected:
	constexpr atomic_base_common()
		: m_value()
	{}

	constexpr atomic_base_common(T desired)
		: m_value(desired)
	{
		hamon::detail::clear_padding_if_needed(m_value);
	}

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

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_COMMON_HPP
