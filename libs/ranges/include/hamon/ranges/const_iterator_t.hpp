/**
 *	@file	const_iterator_t.hpp
 *
 *	@brief	ranges::const_iterator_t の定義
 */

#ifndef HAMON_RANGES_CONST_ITERATOR_T_HPP
#define HAMON_RANGES_CONST_ITERATOR_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::const_iterator_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/const_iterator.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINED_PARAM(ranges::range, R)>
using const_iterator_t = hamon::const_iterator<hamon::ranges::iterator_t<R>>;

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_CONST_ITERATOR_T_HPP
