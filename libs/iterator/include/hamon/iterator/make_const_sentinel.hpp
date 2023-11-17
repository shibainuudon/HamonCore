/**
 *	@file	make_const_sentinel.hpp
 *
 *	@brief	make_const_sentinel の定義
 */

#ifndef HAMON_ITERATOR_MAKE_CONST_SENTINEL_HPP
#define HAMON_ITERATOR_MAKE_CONST_SENTINEL_HPP

#include <hamon/iterator/basic_const_iterator.hpp>

#if defined(HAMON_USE_STD_BASIC_CONST_ITERATOR)

namespace hamon
{

using std::make_const_sentinel;

}	// namespace hamon

#else

#include <hamon/iterator/const_sentinel.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINED_PARAM(hamon::semiregular, S)>
HAMON_CXX11_CONSTEXPR hamon::const_sentinel<S>
make_const_sentinel(S s)
HAMON_NOEXCEPT_IF(hamon::is_nothrow_convertible<S, hamon::const_sentinel<S>>::value)	// noexcept as an extension
{
	return s;
}

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_MAKE_CONST_SENTINEL_HPP
