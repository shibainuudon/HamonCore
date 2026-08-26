/**
 *	@file	crend.hpp
 *
 *	@brief	crend 関数の定義
 */

#ifndef HAMON_ITERATOR_CREND_HPP
#define HAMON_ITERATOR_CREND_HPP

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

#endif // HAMON_ITERATOR_CREND_HPP
