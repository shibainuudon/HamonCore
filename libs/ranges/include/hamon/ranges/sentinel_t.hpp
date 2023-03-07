/**
 *	@file	sentinel_t.hpp
 *
 *	@brief	ranges::sentinel_t の定義
 */

#ifndef HAMON_RANGES_SENTINEL_T_HPP
#define HAMON_RANGES_SENTINEL_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::sentinel_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINED_PARAM(ranges::range, Range)>
using sentinel_t = decltype(ranges::end(hamon::declval<Range&>()));

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_SENTINEL_T_HPP
