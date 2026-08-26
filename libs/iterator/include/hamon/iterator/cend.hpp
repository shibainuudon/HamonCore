/**
 *	@file	cend.hpp
 *
 *	@brief	cend 関数の定義
 */

#ifndef HAMON_ITERATOR_CEND_HPP
#define HAMON_ITERATOR_CEND_HPP

#include <hamon/iterator/end.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
cend(C const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::end(c))
-> decltype(hamon::end(c))
{
	// [iterator.range]/7
	return hamon::end(c);
}

}	// namespace hamon

#endif // HAMON_ITERATOR_CEND_HPP
