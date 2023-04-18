/**
 *	@file	is_specialization_of_subrange.hpp
 *
 *	@brief	is_specialization_of_subrange の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_SUBRANGE_HPP
#define HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_SUBRANGE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 20) && HAMON_HAS_INCLUDE(<ranges>)
#  include <ranges>
#endif

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_subrange
	: public hamon::false_type {};

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911)

template <typename It, typename Sent, std::ranges::subrange_kind Kind>
struct is_specialization_of_subrange<std::ranges::subrange<It, Sent, Kind>>
	: public hamon::true_type {};

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_SUBRANGE_HPP
