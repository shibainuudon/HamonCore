/**
 *	@file	rbegin.hpp
 *
 *	@brief	rbegin 関数の定義
 */

#ifndef HAMON_ITERATOR_RBEGIN_HPP
#define HAMON_ITERATOR_RBEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::rbegin;

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
rbegin(C& c) HAMON_NOEXCEPT_IF_EXPR(c.rbegin())
-> decltype(c.rbegin())
{
	// [iterator.range]/8
	return c.rbegin();
}

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
rbegin(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.rbegin())
-> decltype(c.rbegin())
{
	// [iterator.range]/8
	return c.rbegin();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::reverse_iterator<T*>
rbegin(T (&a)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/10
	return hamon::reverse_iterator<T*>(a + N);
}

template <typename E>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::reverse_iterator<E const*>
rbegin(std::initializer_list<E> il) HAMON_NOEXCEPT
{
	// [iterator.range]/12
	return hamon::reverse_iterator<E const*>(il.end());
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RBEGIN_HPP
