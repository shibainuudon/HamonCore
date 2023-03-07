/**
 *	@file	begin.hpp
 *
 *	@brief	begin 関数の定義
 */

#ifndef HAMON_ITERATOR_BEGIN_HPP
#define HAMON_ITERATOR_BEGIN_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::begin;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
begin(Container& c) -> decltype(c.begin())
{
	return c.begin();
}

template <typename Container>
inline HAMON_CONSTEXPR auto
begin(Container const& c) -> decltype(c.begin())
{
	return c.begin();
}

template <typename T, hamon::size_t N>
inline HAMON_CONSTEXPR T*
begin(T (&a)[N]) HAMON_NOEXCEPT
{
	return a;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_BEGIN_HPP
