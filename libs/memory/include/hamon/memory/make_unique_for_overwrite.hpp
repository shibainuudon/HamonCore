/**
 *	@file	make_unique_for_overwrite.hpp
 *
 *	@brief	make_unique_for_overwrite を定義
 */

#ifndef HAMON_MEMORY_MAKE_UNIQUE_FOR_OVERWRITE_HPP
#define HAMON_MEMORY_MAKE_UNIQUE_FOR_OVERWRITE_HPP

#include <hamon/memory/unique_ptr.hpp>
#include <memory>

#if defined(HAMON_USE_STD_UNIQUE_PTR) && \
	defined(__cpp_lib_smart_ptr_for_overwrite) && (__cpp_lib_smart_ptr_for_overwrite >= 202002L)

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

// 20.3.1.5 Creation[unique.ptr.create]

template <typename T>
HAMON_CXX14_CONSTEXPR
hamon::enable_if_t<!hamon::is_array<T>::value, hamon::unique_ptr<T>>	// [unique.ptr.create]/6
make_unique_for_overwrite()
{
	// [unique.ptr.create]/7
	return hamon::unique_ptr<T>(new T);
}

template <typename T>
HAMON_CXX14_CONSTEXPR
hamon::enable_if_t<hamon::is_unbounded_array<T>::value, hamon::unique_ptr<T>>	// [unique.ptr.create]/8
make_unique_for_overwrite(hamon::size_t n)
{
	// [unique.ptr.create]/9
	return hamon::unique_ptr<T>(new hamon::remove_extent_t<T>[n]);
}

template <typename T, typename... Args>
hamon::enable_if_t<hamon::is_bounded_array<T>::value>	// [unique.ptr.create]/10
make_unique_for_overwrite(Args&&...) = delete;

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_MAKE_UNIQUE_FOR_OVERWRITE_HPP
