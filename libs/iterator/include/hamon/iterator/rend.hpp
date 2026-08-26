/**
 *	@file	rend.hpp
 *
 *	@brief	rend関数の定義
 */

#ifndef HAMON_ITERATOR_REND_HPP
#define HAMON_ITERATOR_REND_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
rend(C& c) HAMON_NOEXCEPT_IF_EXPR(c.rend())
-> decltype(c.rend())
{
	// [iterator.range]/9
	return c.rend();
}

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
rend(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.rend())
-> decltype(c.rend())
{
	// [iterator.range]/9
	return c.rend();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::reverse_iterator<T*>
rend(T (&a)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/11
	return hamon::reverse_iterator<T*>(a);
}

template <typename E>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::reverse_iterator<E const*>
rend(hamon::initializer_list<E> il) HAMON_NOEXCEPT
{
	// [iterator.range]/13
	return hamon::reverse_iterator<E const*>(il.begin());
}

}	// namespace hamon

#endif // HAMON_ITERATOR_REND_HPP
