/**
 *	@file	cbegin.hpp
 *
 *	@brief	cbegin 関数の定義
 */

#ifndef HAMON_ITERATOR_CBEGIN_HPP
#define HAMON_ITERATOR_CBEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::cbegin;

}	// namespace hamon

#else

#include <hamon/iterator/begin.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
cbegin(Container const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::begin(c))
-> decltype(hamon::begin(c))
{
	return hamon::begin(c);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CBEGIN_HPP
