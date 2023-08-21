/**
 *	@file	make_unique_for_overwrite.hpp
 *
 *	@brief	make_unique_for_overwrite を定義
 */

#ifndef HAMON_MEMORY_MAKE_UNIQUE_FOR_OVERWRITE_HPP
#define HAMON_MEMORY_MAKE_UNIQUE_FOR_OVERWRITE_HPP

#include <memory>

#if defined(__cpp_lib_smart_ptr_for_overwrite) && (__cpp_lib_smart_ptr_for_overwrite >= 202002L)

namespace hamon
{

using std::make_unique_for_overwrite;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T>
inline /*HAMON_CXX23_CONSTEXPR*/
hamon::enable_if_t<!hamon::is_array<T>::value, std::unique_ptr<T>>
make_unique_for_overwrite()
{
	return std::unique_ptr<T>(new T);
}

template <typename T>
inline /*HAMON_CXX23_CONSTEXPR*/
hamon::enable_if_t<hamon::is_unbounded_array<T>::value, std::unique_ptr<T>>
make_unique_for_overwrite(hamon::size_t n)
{
	return std::unique_ptr<T>(new hamon::remove_extent_t<T>[n]);
}

template <typename T, typename... Args>
hamon::enable_if_t<hamon::is_bounded_array<T>::value>
make_unique_for_overwrite(Args&&...) = delete;

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_MAKE_UNIQUE_FOR_OVERWRITE_HPP
