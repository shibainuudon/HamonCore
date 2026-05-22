/**
 *	@file	size.hpp
 *
 *	@brief	size 関数の定義
 */

#ifndef HAMON_ITERATOR_SIZE_HPP
#define HAMON_ITERATOR_SIZE_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::size;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
size(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.size())
-> decltype(c.size())
{
	// [iterator.range]/16
	return c.size();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
size(T const (&)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/17
	return N;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_SIZE_HPP
