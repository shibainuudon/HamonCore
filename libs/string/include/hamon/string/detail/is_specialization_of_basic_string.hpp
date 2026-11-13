/**
 *	@file	is_specialization_of_basic_string.hpp
 *
 *	@brief	is_specialization_of_basic_string の定義
 */

#ifndef HAMON_STRING_DETAIL_IS_SPECIALIZATION_OF_BASIC_STRING_HPP
#define HAMON_STRING_DETAIL_IS_SPECIALIZATION_OF_BASIC_STRING_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <string>
#endif

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_basic_string
	: public hamon::false_type {};

#if !defined(HAMON_NO_STD)
template <typename CharT, typename Traits, typename Allocator>
struct is_specialization_of_basic_string<std::basic_string<CharT, Traits, Allocator>>
	: public hamon::true_type {};
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STRING_DETAIL_IS_SPECIALIZATION_OF_BASIC_STRING_HPP
