/**
 *	@file	subrange_kind.hpp
 *
 *	@brief	subrange_kind の定義
 */

#ifndef HAMON_RANGES_UTILITY_SUBRANGE_KIND_HPP
#define HAMON_RANGES_UTILITY_SUBRANGE_KIND_HPP

namespace hamon {
namespace ranges {

enum class subrange_kind : bool { unsized, sized };

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_SUBRANGE_KIND_HPP
