/**
 *	@file	make_unique.hpp
 *
 *	@brief	make_unique を定義
 */

#ifndef HAMON_MEMORY_MAKE_UNIQUE_HPP
#define HAMON_MEMORY_MAKE_UNIQUE_HPP

#include <hamon/memory/unique_ptr.hpp>
#include <memory>

#if defined(HAMON_USE_STD_UNIQUE_PTR) && \
	defined(__cpp_lib_make_unique) && (__cpp_lib_make_unique >= 201304)

namespace hamon
{

using std::make_unique;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.1.5 Creation[unique.ptr.create]

template <typename T, typename... Args>
HAMON_CXX14_CONSTEXPR
hamon::enable_if_t<!hamon::is_array<T>::value, hamon::unique_ptr<T>>	// [unique.ptr.create]/1
make_unique(Args&&... args)
{
	// [unique.ptr.create]/2
	return hamon::unique_ptr<T>(new T(hamon::forward<Args>(args)...));
}

template <typename T>
HAMON_CXX14_CONSTEXPR
hamon::enable_if_t<hamon::is_unbounded_array<T>::value, hamon::unique_ptr<T>>	// [unique.ptr.create]/3
make_unique(hamon::size_t n)
{
	// [unique.ptr.create]/4
	return hamon::unique_ptr<T>(new hamon::remove_extent_t<T>[n]{});
}

template <typename T, typename... Args>
hamon::enable_if_t<hamon::is_bounded_array<T>::value>	// [unique.ptr.create]/5
make_unique(Args&&...) = delete;

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_MAKE_UNIQUE_HPP
