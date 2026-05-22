/**
 *	@file	begin.hpp
 *
 *	@brief	begin 関数の定義
 */

#ifndef HAMON_ITERATOR_BEGIN_HPP
#define HAMON_ITERATOR_BEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::begin;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
begin(C& c) HAMON_NOEXCEPT_IF_EXPR(c.begin())
-> decltype(c.begin())
{
	// [iterator.range]/2
	return c.begin();
}

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
begin(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.begin())
-> decltype(c.begin())
{
	// [iterator.range]/2
	return c.begin();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T*
begin(T (&a)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/4
	return a;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_BEGIN_HPP
