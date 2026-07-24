/**
 *	@file	concat_reference_t.hpp
 *
 *	@brief	concat_reference_t の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_CONCAT_REFERENCE_T_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_CONCAT_REFERENCE_T_HPP

#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/type_traits/common_reference.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// 25.7.18.2 Class template concat_view[range.concat.view]

template <typename... Rs>
using concat_reference_t = hamon::common_reference_t<hamon::ranges::range_reference_t<Rs>...>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_CONCAT_REFERENCE_T_HPP
