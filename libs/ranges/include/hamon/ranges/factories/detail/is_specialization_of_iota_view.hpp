/**
 *	@file	is_specialization_of_iota_view.hpp
 *
 *	@brief	is_specialization_of_iota_view の定義
 */

#ifndef HAMON_RANGES_FACTORIES_DETAIL_IS_SPECIALIZATION_OF_IOTA_VIEW_HPP
#define HAMON_RANGES_FACTORIES_DETAIL_IS_SPECIALIZATION_OF_IOTA_VIEW_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

namespace hamon {
namespace detail {

template <typename T>
struct is_specialization_of_iota_view
	: public hamon::false_type {};

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L)

template <typename W, typename Bound>
struct is_specialization_of_iota_view<std::ranges::iota_view<W, Bound>>
	: public hamon::true_type {};

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_RANGES_FACTORIES_DETAIL_IS_SPECIALIZATION_OF_IOTA_VIEW_HPP
