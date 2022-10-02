/**
 *	@file	crend.hpp
 *
 *	@brief	crend 関数の定義
 */

#ifndef HAMON_ITERATOR_CREND_HPP
#define HAMON_ITERATOR_CREND_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::crend;

}	// namespace hamon

#else

#include <hamon/iterator/rend.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
crend(Container const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::rend(c))
-> decltype(hamon::rend(c))
{
	return hamon::rend(c);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CREND_HPP
