/**
 *	@file	reinterpret_pointer_cast.hpp
 *
 *	@brief	reinterpret_pointer_cast の定義
 */

#ifndef HAMON_MEMORY_REINTERPRET_POINTER_CAST_HPP
#define HAMON_MEMORY_REINTERPRET_POINTER_CAST_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR)

namespace hamon
{

using std::reinterpret_pointer_cast;

}	// namespace hamon

#else

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.2.10 Casts[util.smartptr.shared.cast]

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::shared_ptr<T>	// nodiscard as an extension
reinterpret_pointer_cast(hamon::shared_ptr<U> const& r) noexcept
{
	// [util.smartptr.shared.cast]/12
	return hamon::shared_ptr<T>(r,
		reinterpret_cast<typename hamon::shared_ptr<T>::element_type*>(r.get()));
}

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::shared_ptr<T>	// nodiscard as an extension
reinterpret_pointer_cast(hamon::shared_ptr<U>&& r) noexcept
{
	// [util.smartptr.shared.cast]/12
	return hamon::shared_ptr<T>(hamon::move(r),
		reinterpret_cast<typename hamon::shared_ptr<T>::element_type*>(r.get()));
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_REINTERPRET_POINTER_CAST_HPP
