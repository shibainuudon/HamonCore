/**
 *	@file	concat_value_t.hpp
 *
 *	@brief	concat_value_t の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_CONCAT_VALUE_T_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_CONCAT_VALUE_T_HPP

#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/common_type.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// 25.7.18.2 Class template concat_view[range.concat.view]

template <typename... Rs>
using concat_value_t = hamon::common_type_t<hamon::ranges::range_value_t<Rs>...>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_CONCAT_VALUE_T_HPP
