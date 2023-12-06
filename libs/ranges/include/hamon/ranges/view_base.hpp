/**
 *	@file	view_base.hpp
 *
 *	@brief	view_base の定義
 */

#ifndef HAMON_RANGES_VIEW_BASE_HPP
#define HAMON_RANGES_VIEW_BASE_HPP

#include <hamon/ranges/config.hpp>

namespace hamon {
namespace ranges {

// [range.view], views

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::view_base;

#else

struct view_base {};

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEW_BASE_HPP
