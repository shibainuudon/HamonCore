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

template <typename Container>
inline HAMON_CONSTEXPR auto
cend(Container const& c)
HAMON_NOEXCEPT_IF_EXPR(hamon::end(c))
-> decltype(hamon::end(c))
{
	return hamon::end(c);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CEND_HPP
