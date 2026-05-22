/**
 *	@file	cend.hpp
 *
 *	@brief	cend 関数の定義
 */

#ifndef HAMON_ITERATOR_CEND_HPP
#define HAMON_ITERATOR_CEND_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::cend;

}	// namespace hamon

#else

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

#endif

#endif // HAMON_ITERATOR_CEND_HPP
