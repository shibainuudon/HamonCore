/**
 *	@file	dynamic_pointer_cast.hpp
 *
 *	@brief	dynamic_pointer_cast の定義
 */

#ifndef HAMON_MEMORY_DYNAMIC_POINTER_CAST_HPP
#define HAMON_MEMORY_DYNAMIC_POINTER_CAST_HPP

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.2.10 Casts[util.smartptr.shared.cast]

#if !defined(HAMON_NO_RTTI)
template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::shared_ptr<T>	// nodiscard as an extension
dynamic_pointer_cast(hamon::shared_ptr<U> const& r) noexcept
{
	// [util.smartptr.shared.cast]/6
	auto const p = dynamic_cast<typename hamon::shared_ptr<T>::element_type*>(r.get());
	if (p)
	{
		return hamon::shared_ptr<T>(r, p);
	}
	return hamon::shared_ptr<T>();
}

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR hamon::shared_ptr<T>	// nodiscard as an extension
dynamic_pointer_cast(hamon::shared_ptr<U>&& r) noexcept
{
	// [util.smartptr.shared.cast]/6
	auto const p = dynamic_cast<typename hamon::shared_ptr<T>::element_type*>(r.get());
	if (p)
	{
		return hamon::shared_ptr<T>(hamon::move(r), p);
	}
	return hamon::shared_ptr<T>();
}
#endif

}	// namespace hamon

#endif // HAMON_MEMORY_DYNAMIC_POINTER_CAST_HPP
