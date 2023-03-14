/**
 *	@file	to_array.hpp
 *
 *	@brief	to_array 関数テンプレートの定義
 */

#ifndef HAMON_ARRAY_TO_ARRAY_HPP
#define HAMON_ARRAY_TO_ARRAY_HPP

#include <hamon/array/config.hpp>
#include <array>

#if defined(HAMON_USE_STD_ARRAY) &&	\
	defined(__cpp_lib_to_array) && (__cpp_lib_to_array >= 201907L)

namespace hamon
{

using std::to_array;

}	// namespace hamon

#else

#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T, hamon::size_t N, hamon::size_t... I>
inline HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array_impl(T (&a)[N], hamon::index_sequence<I...>)
{
	// [array.creation]/3
	return {{a[I]...}};
}

template <typename T, hamon::size_t N, hamon::size_t... I>
inline HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array_impl(T (&&a)[N], hamon::index_sequence<I...>)
{
	// [array.creation]/6
	return {{hamon::move(a[I])...}};
}

}	// namespace detail

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array(T (&a)[N])
HAMON_NOEXCEPT_IF(hamon::is_nothrow_copy_constructible<T>::value)
{
	// [array.creation]/1
	static_assert(!hamon::is_array<T>::value, "");
	static_assert(hamon::is_copy_constructible<T>::value, "");
	return hamon::detail::to_array_impl(a, hamon::make_index_sequence<N>{});
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array(T (&&a)[N])
HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<T>::value)
{
	// [array.creation]/4
	static_assert(!hamon::is_array<T>::value, "");
	static_assert(hamon::is_move_constructible<T>::value, "");
	return hamon::detail::to_array_impl(hamon::move(a), hamon::make_index_sequence<N>{});
}

}	// namespace hamon

#endif

#endif // HAMON_ARRAY_TO_ARRAY_HPP
