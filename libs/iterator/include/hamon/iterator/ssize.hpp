/**
 *	@file	ssize.hpp
 *
 *	@brief	ssize 関数の定義
 */

#ifndef HAMON_ITERATOR_SSIZE_HPP
#define HAMON_ITERATOR_SSIZE_HPP

#include <iterator>

#if defined(__cpp_lib_ssize) && (__cpp_lib_ssize >= 201902)

namespace hamon
{

using std::ssize;

}	// namespace hamon

#else

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename C>
HAMON_CONSTEXPR auto ssize(C const& c)
-> hamon::common_type_t<
	hamon::ptrdiff_t,
	hamon::make_signed_t<decltype(c.size())>>
{
	using R = hamon::common_type_t<
		hamon::ptrdiff_t,
		hamon::make_signed_t<decltype(c.size())>>;
	return static_cast<R>(c.size());
}

template <typename T, hamon::ptrdiff_t N>
HAMON_CONSTEXPR hamon::ptrdiff_t
ssize(T const(&)[N]) HAMON_NOEXCEPT
{
	return N;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_SSIZE_HPP
