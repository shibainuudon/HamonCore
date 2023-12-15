/**
 *	@file	is_specialization_of_basic_string_view.hpp
 *
 *	@brief	is_specialization_of_basic_string_view の定義
 */

#ifndef HAMON_STRING_VIEW_DETAIL_IS_SPECIALIZATION_OF_BASIC_STRING_VIEW_HPP
#define HAMON_STRING_VIEW_DETAIL_IS_SPECIALIZATION_OF_BASIC_STRING_VIEW_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<string_view>)
#  include <string_view>
#endif

namespace hamon
{
namespace detail
{

template <typename T>
struct is_specialization_of_basic_string_view
	: public hamon::false_type {};

#if defined(__cpp_lib_string_view) && (__cpp_lib_string_view >= 201606L)

template <typename CharT, typename Traits>
struct is_specialization_of_basic_string_view<std::basic_string_view<CharT, Traits>>
	: public hamon::true_type {};

#endif

}	// namespace detail
}	// namespace hamon


#endif // HAMON_STRING_VIEW_DETAIL_IS_SPECIALIZATION_OF_BASIC_STRING_VIEW_HPP
