/**
 *	@file	make_shared_for_overwrite.hpp
 *
 *	@brief	make_shared_for_overwrite の定義
 */

#ifndef HAMON_MEMORY_MAKE_SHARED_FOR_OVERWRITE_HPP
#define HAMON_MEMORY_MAKE_SHARED_FOR_OVERWRITE_HPP

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/detail/sp_access.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.2.7 Creation[util.smartptr.shared.create]

template <typename T, typename = hamon::enable_if_t<!hamon::is_unbounded_array<T>::value>>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared_for_overwrite()
{
	return hamon::detail::sp_access::make_shared_for_overwrite<T>();
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unbounded_array<T>::value>>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared_for_overwrite(hamon::size_t N)
{
	return hamon::detail::sp_access::make_shared_for_overwrite<T>(N);
}

}	// namespace hamon

#endif // HAMON_MEMORY_MAKE_SHARED_FOR_OVERWRITE_HPP
