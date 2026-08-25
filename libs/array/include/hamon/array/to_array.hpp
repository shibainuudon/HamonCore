/**
 *	@file	to_array.hpp
 *
 *	@brief	to_array 関数テンプレートの定義
 */

#ifndef HAMON_ARRAY_TO_ARRAY_HPP
#define HAMON_ARRAY_TO_ARRAY_HPP

#include <hamon/array/array.hpp>
#include <hamon/concepts/detail/cpp17_copy_constructible.hpp>
#include <hamon/concepts/detail/cpp17_move_constructible.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_constructible.hpp>
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
HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array_impl(T (&a)[N], hamon::index_sequence<I...>)
{
	// [array.creation]/3
	return {{a[I]...}};
}

template <typename T, hamon::size_t N, hamon::size_t... I>
HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array_impl(T (&&a)[N], hamon::index_sequence<I...>)
{
	// [array.creation]/6
	return {{hamon::move(a[I])...}};
}

}	// namespace detail

// 24.3.7.6 Array creation functions[array.creation]

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array(T (&a)[N])
HAMON_NOEXCEPT_IF(hamon::is_nothrow_copy_constructible<T>::value)	// noexcept as an extension
{
	// [array.creation]/1
	static_assert(!hamon::is_array_v<T>, "");
	static_assert(hamon::is_constructible_v<hamon::remove_cv_t<T>, T&>, "");

	// [array.creation]/2
	static_assert(hamon::detail::cpp17_copy_constructible<T>, "");

	return hamon::detail::to_array_impl(a, hamon::make_index_sequence<N>{});
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::array<hamon::remove_cv_t<T>, N>
to_array(T (&&a)[N])
HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<T>::value)	// noexcept as an extension
{
	// [array.creation]/4
	static_assert(!hamon::is_array_v<T>, "");
	static_assert(hamon::is_constructible_v<hamon::remove_cv_t<T>, T>, "");

	// [array.creation]/5
	static_assert(hamon::detail::cpp17_move_constructible<T>, "");

	return hamon::detail::to_array_impl(hamon::move(a), hamon::make_index_sequence<N>{});
}

}	// namespace hamon

#endif // HAMON_ARRAY_TO_ARRAY_HPP
