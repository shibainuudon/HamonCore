/**
 *	@file	prev.hpp
 *
 *	@brief	ranges::prev 関数の実装
 */

#ifndef HAMON_ITERATOR_RANGES_PREV_HPP
#define HAMON_ITERATOR_RANGES_PREV_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{
namespace ranges
{

using std::ranges::prev;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, It)>
inline HAMON_CXX14_CONSTEXPR It
prev(It x)
{
	--x;
	return x;
}

template <HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, It)>
inline HAMON_CXX14_CONSTEXPR It
prev(It x, hamon::iter_difference_t<It> n)
{
	ranges::advance(x, -n);
	return x;
}

template <HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, It)>
inline HAMON_CXX14_CONSTEXPR It
prev(It x, hamon::iter_difference_t<It> n, It bound)
{
	ranges::advance(x, -n, bound);
	return x;
}

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RANGES_PREV_HPP
