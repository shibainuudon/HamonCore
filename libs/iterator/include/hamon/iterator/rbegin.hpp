/**
 *	@file	rbegin.hpp
 *
 *	@brief	rbegin 関数の定義
 */

#ifndef HAMON_ITERATOR_RBEGIN_HPP
#define HAMON_ITERATOR_RBEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::rbegin;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
rbegin(Container& c) -> decltype(c.rbegin())
{
	return c.rbegin();
}

template <typename Container>
inline HAMON_CONSTEXPR auto
rbegin(Container const& c) -> decltype(c.rbegin())
{
	return c.rbegin();
}

template <typename T, hamon::size_t N>
inline HAMON_CONSTEXPR hamon::reverse_iterator<T*>
rbegin(T (&a)[N]) HAMON_NOEXCEPT
{
	return hamon::reverse_iterator<T*>(a + N);
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RBEGIN_HPP
