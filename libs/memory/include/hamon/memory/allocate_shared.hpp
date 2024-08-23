/**
 *	@file	allocate_shared.hpp
 *
 *	@brief	allocate_shared の定義
 */

#ifndef HAMON_MEMORY_ALLOCATE_SHARED_HPP
#define HAMON_MEMORY_ALLOCATE_SHARED_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR)

namespace hamon
{

using std::allocate_shared;

}	// namespace hamon

#else

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/detail/sp_access.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_md.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_md.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.2.7 Creation[util.smartptr.shared.create]

template <typename T, typename = hamon::enable_if_t<!hamon::is_array<T>::value>, typename A, typename... Args>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared(A const& a, Args&&... args)
{
	return hamon::detail::sp_access::allocate_shared<T>(a, hamon::forward<Args>(args)...);
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unbounded_array<T>::value>, typename A>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared(A const& a, hamon::size_t N)
{
	auto sp = hamon::detail::sp_access::allocate_shared_for_overwrite<T>(a, N);
	hamon::detail::uninitialized_value_construct_n_md(sp.get(), N);
	return sp;
}

template <typename T, typename = hamon::enable_if_t<hamon::is_bounded_array<T>::value>, typename A>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared(A const& a)
{
	constexpr hamon::size_t N = hamon::extent<T>::value;
	auto sp = hamon::detail::sp_access::allocate_shared_for_overwrite<T>(a, N);
	hamon::detail::uninitialized_value_construct_n_md(sp.get(), N);
	return sp;
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unbounded_array<T>::value>, typename A>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared(A const& a, hamon::size_t N, hamon::remove_extent_t<T> const& u)
{
	auto sp = hamon::detail::sp_access::allocate_shared_for_overwrite<T>(a, N);
	hamon::detail::uninitialized_fill_n_md(sp.get(), N, u);
	return sp;
}

template <typename T, typename = hamon::enable_if_t<hamon::is_bounded_array<T>::value>, typename A>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
allocate_shared(A const& a, hamon::remove_extent_t<T> const& u)
{
	constexpr hamon::size_t N = hamon::extent<T>::value;
	auto sp = hamon::detail::sp_access::allocate_shared_for_overwrite<T>(a);
	hamon::detail::uninitialized_fill_n_md(sp.get(), N, u);
	return sp;
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ALLOCATE_SHARED_HPP
