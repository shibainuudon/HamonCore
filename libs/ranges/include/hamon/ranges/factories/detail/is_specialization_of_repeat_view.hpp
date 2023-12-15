/**
 *	@file	is_specialization_of_repeat_view.hpp
 *
 *	@brief	is_specialization_of_repeat_view の定義
 */

#ifndef HAMON_RANGES_FACTORIES_DETAIL_IS_SPECIALIZATION_OF_REPEAT_VIEW_HPP
#define HAMON_RANGES_FACTORIES_DETAIL_IS_SPECIALIZATION_OF_REPEAT_VIEW_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

namespace hamon {
namespace detail {

template <typename T>
struct is_specialization_of_repeat_view
	: public hamon::false_type {};

#if defined(__cpp_lib_ranges_repeat) && (__cpp_lib_ranges_repeat >= 202207L)

template <typename T, typename Bound>
struct is_specialization_of_repeat_view<std::ranges::repeat_view<T, Bound>>
	: public hamon::true_type {};

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_RANGES_FACTORIES_DETAIL_IS_SPECIALIZATION_OF_REPEAT_VIEW_HPP
