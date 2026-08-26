/**
 *	@file	cbegin.hpp
 *
 *	@brief	cbegin 関数の定義
 */

#ifndef HAMON_ITERATOR_CBEGIN_HPP
#define HAMON_ITERATOR_CBEGIN_HPP

#include <hamon/iterator/begin.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
cbegin(C const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::begin(c))
-> decltype(hamon::begin(c))
{
	// [iterator.range]/6
	return hamon::begin(c);
}

}	// namespace hamon

#endif // HAMON_ITERATOR_CBEGIN_HPP
