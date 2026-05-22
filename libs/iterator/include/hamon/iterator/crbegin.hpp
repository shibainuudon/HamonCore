/**
 *	@file	crbegin.hpp
 *
 *	@brief	crbegin 関数の定義
 */

#ifndef HAMON_ITERATOR_CRBEGIN_HPP
#define HAMON_ITERATOR_CRBEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::crbegin;

}	// namespace hamon

#else

#include <hamon/iterator/rbegin.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
crbegin(C const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::rbegin(c))
-> decltype(hamon::rbegin(c))
{
	// [iterator.range]/14
	return hamon::rbegin(c);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CRBEGIN_HPP
