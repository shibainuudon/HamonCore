/**
 *	@file	crbegin.hpp
 *
 *	@brief	crbegin 関数の定義
 */

#ifndef HAMON_ITERATOR_CRBEGIN_HPP
#define HAMON_ITERATOR_CRBEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::crbegin;

}	// namespace hamon

#else

#include <hamon/iterator/rbegin.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
crbegin(Container const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::rbegin(c))
-> decltype(hamon::rbegin(c))
{
	return hamon::rbegin(c);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CRBEGIN_HPP
