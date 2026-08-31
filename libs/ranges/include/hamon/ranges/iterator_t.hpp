/**
 *	@file	iterator_t.hpp
 *
 *	@brief	ranges::iterator_t の定義
 */

#ifndef HAMON_RANGES_ITERATOR_T_HPP
#define HAMON_RANGES_ITERATOR_T_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon {
namespace ranges {

// [ranges.syn]
template <typename T>
using iterator_t = decltype(ranges::begin(hamon::declval<T&>()));

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ITERATOR_T_HPP
