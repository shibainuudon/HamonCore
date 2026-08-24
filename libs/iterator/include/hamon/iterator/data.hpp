/**
 *	@file	data.hpp
 *
 *	@brief	data 関数の定義
 */

#ifndef HAMON_ITERATOR_DATA_HPP
#define HAMON_ITERATOR_DATA_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::data;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
data(C& c) HAMON_NOEXCEPT_IF_EXPR(c.data())
-> decltype(c.data())
{
	// [iterator.range]/22
	return c.data();
}

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
data(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.data())
-> decltype(c.data())
{
	// [iterator.range]/22
	return c.data();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T*
data(T (&a)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/23
	return a;
}

#if !(defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L))

template <typename E>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR const E*
data(hamon::initializer_list<E> il) HAMON_NOEXCEPT
{
	return il.begin();
}

#endif

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_DATA_HPP
