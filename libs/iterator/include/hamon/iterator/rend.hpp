/**
 *	@file	rend.hpp
 *
 *	@brief	rend関数の定義
 */

#ifndef HAMON_ITERATOR_REND_HPP
#define HAMON_ITERATOR_REND_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::rend;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

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
rend(std::initializer_list<E> il) HAMON_NOEXCEPT
{
	// [iterator.range]/13
	return hamon::reverse_iterator<E const*>(il.begin());
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_REND_HPP
