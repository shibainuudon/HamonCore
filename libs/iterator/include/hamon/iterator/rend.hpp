/**
 *	@file	rend.hpp
 *
 *	@brief	rend関数の定義
 */

#ifndef HAMON_ITERATOR_REND_HPP
#define HAMON_ITERATOR_REND_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::rend;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
rend(Container& c) -> decltype(c.rend())
{
	return c.rend();
}

template <typename Container>
inline HAMON_CONSTEXPR auto
rend(Container const& c) -> decltype(c.rend())
{
	return c.rend();
}

template <typename T, hamon::size_t N>
inline HAMON_CONSTEXPR hamon::reverse_iterator<T*>
rend(T (&a)[N]) HAMON_NOEXCEPT
{
	return hamon::reverse_iterator<T*>(a);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_REND_HPP
