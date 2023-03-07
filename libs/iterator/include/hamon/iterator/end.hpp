/**
 *	@file	end.hpp
 *
 *	@brief	end 関数の定義
 */

#ifndef HAMON_ITERATOR_END_HPP
#define HAMON_ITERATOR_END_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR)

namespace hamon
{

using std::end;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Container>
inline HAMON_CONSTEXPR auto
end(Container& c) -> decltype(c.end())
{
	return c.end();
}

template <typename Container>
inline HAMON_CONSTEXPR auto
end(Container const& c) -> decltype(c.end())
{
	return c.end();
}

template <typename T, hamon::size_t N>
inline HAMON_CONSTEXPR T*
end(T (&a)[N]) HAMON_NOEXCEPT
{
	return a + N;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_END_HPP
