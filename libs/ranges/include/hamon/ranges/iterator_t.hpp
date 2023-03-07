/**
 *	@file	iterator_t.hpp
 *
 *	@brief	ranges::iterator_t の定義
 */

#ifndef HAMON_RANGES_ITERATOR_T_HPP
#define HAMON_RANGES_ITERATOR_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::iterator_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/begin.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon {
namespace ranges {

template <typename T>
using iterator_t = decltype(ranges::begin(hamon::declval<T&>()));

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ITERATOR_T_HPP
