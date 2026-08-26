/**
 *	@file	allocate_shared_for_overwrite.hpp
 *
 *	@brief	allocate_shared_for_overwrite の定義
 */

#ifndef HAMON_MEMORY_ALLOCATE_SHARED_FOR_OVERWRITE_HPP
#define HAMON_MEMORY_ALLOCATE_SHARED_FOR_OVERWRITE_HPP

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/detail/sp_access.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.2.7 Creation[util.smartptr.shared.create]

template <typename T, typename = hamon::enable_if_t<!hamon::is_unbounded_array<T>::value>, typename A>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared_for_overwrite(A const& a)
{
	return hamon::detail::sp_access::allocate_shared_for_overwrite<T>(a);
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unbounded_array<T>::value>, typename A>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared_for_overwrite(A const& a, hamon::size_t N)
{
	return hamon::detail::sp_access::allocate_shared_for_overwrite<T>(a, N);
}

}	// namespace hamon

#endif // HAMON_MEMORY_ALLOCATE_SHARED_FOR_OVERWRITE_HPP
