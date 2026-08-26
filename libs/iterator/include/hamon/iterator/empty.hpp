/**
 *	@file	empty.hpp
 *
 *	@brief	empty 関数の定義
 */

#ifndef HAMON_ITERATOR_EMPTY_HPP
#define HAMON_ITERATOR_EMPTY_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
empty(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.empty())
-> decltype(c.empty())
{
	// [iterator.range]/20
	return c.empty();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
empty(T const (&)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/21
	return false;
}

#if !(defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L))
// C++26 で initializer_list にメンバ関数 empty() が追加されたため、このオーバーロードは不要になった
template <typename E>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
empty(hamon::initializer_list<E> il) HAMON_NOEXCEPT
{
	return il.size() == 0;
}

#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_EMPTY_HPP
