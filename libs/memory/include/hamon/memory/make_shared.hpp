/**
 *	@file	make_shared.hpp
 *
 *	@brief	make_shared の定義
 */

#ifndef HAMON_MEMORY_MAKE_SHARED_HPP
#define HAMON_MEMORY_MAKE_SHARED_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR) && \
	defined(__cpp_lib_shared_ptr_arrays) && (__cpp_lib_shared_ptr_arrays >= 201707L)

namespace hamon
{

using std::make_shared;

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

template <typename T, typename = hamon::enable_if_t<!hamon::is_array<T>::value>, typename... Args>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared(Args&&... args)
{
	return hamon::detail::sp_access::make_shared<T>(hamon::forward<Args>(args)...);
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unbounded_array<T>::value>>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared(hamon::size_t N)
{
	auto sp = hamon::detail::sp_access::make_shared_for_overwrite<T>(N);
	hamon::detail::uninitialized_value_construct_n_md(sp.get(), N);
	return sp;
}

template <typename T, typename = hamon::enable_if_t<hamon::is_bounded_array<T>::value>>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared()
{
	constexpr hamon::size_t N = hamon::extent<T>::value;
	auto sp = hamon::detail::sp_access::make_shared_for_overwrite<T>(N);
	hamon::detail::uninitialized_value_construct_n_md(sp.get(), N);
	return sp;
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unbounded_array<T>::value>>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared(hamon::size_t N, hamon::remove_extent_t<T> const& u)
{
	auto sp = hamon::detail::sp_access::make_shared_for_overwrite<T>(N);
	hamon::detail::uninitialized_fill_n_md(sp.get(), N, u);
	return sp;
}

template <typename T, typename = hamon::enable_if_t<hamon::is_bounded_array<T>::value>>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR shared_ptr<T>	// nodiscard as an extension
make_shared(hamon::remove_extent_t<T> const& u)
{
	constexpr hamon::size_t N = hamon::extent<T>::value;
	auto sp = hamon::detail::sp_access::make_shared_for_overwrite<T>();
	hamon::detail::uninitialized_fill_n_md(sp.get(), N, u);
	return sp;
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_MAKE_SHARED_HPP
