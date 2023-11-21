/**
 *	@file	const_sentinel.hpp
 *
 *	@brief	const_sentinel の定義
 */

#ifndef HAMON_ITERATOR_CONST_SENTINEL_HPP
#define HAMON_ITERATOR_CONST_SENTINEL_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::const_sentinel;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/const_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{

// [const.iterators.alias]

namespace detail
{

template <typename S, typename = void>
struct const_sentinel_impl
{
	using type = S;
};

template <typename S>
struct const_sentinel_impl<S,
	hamon::enable_if_t<hamon::input_iterator_t<S>::value>>
{
	using type = hamon::const_iterator<S>;
};

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::semiregular, S)>
using const_sentinel =
	typename detail::const_sentinel_impl<S>::type;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CONST_SENTINEL_HPP
