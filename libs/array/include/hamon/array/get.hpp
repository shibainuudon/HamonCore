/**
 *	@file	get.hpp
 *
 *	@brief	get 関数テンプレートの定義
 */

#ifndef HAMON_ARRAY_GET_HPP
#define HAMON_ARRAY_GET_HPP

#include <hamon/array/config.hpp>

#if defined(HAMON_USE_STD_ARRAY)

#include <array>

namespace hamon
{

using std::get;

}	// namespace hamon

#else

#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <hamon::size_t I, typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T&
get(array<T, N>& arr) HAMON_NOEXCEPT
{
	// [array.tuple]/2
	static_assert(I < N, "index is out of bounds");
	return arr[I];
}

template <hamon::size_t I, typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T&&
get(array<T, N>&& arr) HAMON_NOEXCEPT
{
	// [array.tuple]/2
	static_assert(I < N, "index is out of bounds");
	return hamon::move(hamon::get<I>(arr));
}

template <hamon::size_t I, typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T const&
get(array<T, N> const& arr) HAMON_NOEXCEPT
{
	// [array.tuple]/2
	static_assert(I < N, "index is out of bounds");
	return arr[I];
}

template <hamon::size_t I, typename T, hamon::size_t N>
HAMON_NODISCARD	// extension
inline HAMON_CXX11_CONSTEXPR T const&&
get(array<T, N> const&& arr) HAMON_NOEXCEPT
{
	// [array.tuple]/2
	static_assert(I < N, "index is out of bounds");
	return hamon::move(hamon::get<I>(arr));
}

}	// namespace hamon

#endif

#endif // HAMON_ARRAY_GET_HPP
