/**
 *	@file	crend.hpp
 *
 *	@brief	crend 関数の定義
 */

#ifndef HAMON_ITERATOR_CREND_HPP
#define HAMON_ITERATOR_CREND_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::crend;

}	// namespace hamon

#else

#include <hamon/iterator/rend.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
crend(C const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::rend(c))
-> decltype(hamon::rend(c))
{
	// [iterator.range]/15
	return hamon::rend(c);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CREND_HPP
