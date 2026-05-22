/**
 *	@file	end.hpp
 *
 *	@brief	end 関数の定義
 */

#ifndef HAMON_ITERATOR_END_HPP
#define HAMON_ITERATOR_END_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_ITERATOR) && \
	defined(__cpp_lib_initializer_list) && (__cpp_lib_initializer_list >= 202511L)

namespace hamon
{

using std::end;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
end(C& c) HAMON_NOEXCEPT_IF_EXPR(c.end())
-> decltype(c.end())
{
	// [iterator.range]/3
	return c.end();
}

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
end(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.end())
-> decltype(c.end())
{
	// [iterator.range]/3
	return c.end();
}

template <typename T, hamon::size_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T*
end(T (&a)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/5
	return a + N;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_END_HPP
