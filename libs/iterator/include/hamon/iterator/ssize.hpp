/**
 *	@file	ssize.hpp
 *
 *	@brief	ssize 関数の定義
 */

#ifndef HAMON_ITERATOR_SSIZE_HPP
#define HAMON_ITERATOR_SSIZE_HPP

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.7 Range access[iterator.range]

template <typename C>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
ssize(C const& c) HAMON_NOEXCEPT_IF_EXPR(c.size())
-> hamon::common_type_t<
	hamon::ptrdiff_t,
	hamon::make_signed_t<decltype(c.size())>>
{
	// [iterator.range]/18
	using R = hamon::common_type_t<
		hamon::ptrdiff_t,
		hamon::make_signed_t<decltype(c.size())>>;
	return static_cast<R>(c.size());
}

template <typename T, hamon::ptrdiff_t N>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::ptrdiff_t
ssize(T const(&)[N]) HAMON_NOEXCEPT
{
	// [iterator.range]/19
	return N;
}

}	// namespace hamon

#endif // HAMON_ITERATOR_SSIZE_HPP
