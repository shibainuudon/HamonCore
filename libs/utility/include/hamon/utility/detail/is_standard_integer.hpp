/**
 *	@file	is_standard_integer.hpp
 *
 *	@brief	is_standard_integer の定義
 */

#ifndef HAMON_UTILITY_DETAIL_IS_STANDARD_INTEGER_HPP
#define HAMON_UTILITY_DETAIL_IS_STANDARD_INTEGER_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

// is_standard_signed_integer
template <typename T, typename... Types>
using is_standard_signed_integer_impl =
	hamon::disjunction<std::is_same<T, Types>...>;

template <typename T>
using is_standard_signed_integer =
	is_standard_signed_integer_impl<
		hamon::remove_cv_t<T>,
		signed char,
		signed short,
		signed int,
		signed long,
		signed long long
	>;

// is_standard_unsigned_integer
template <typename T, typename... Types>
using is_standard_unsigned_integer_impl =
	hamon::disjunction<std::is_same<T, Types>...>;

template <typename T>
using is_standard_unsigned_integer =
	is_standard_unsigned_integer_impl<
		hamon::remove_cv_t<T>,
		unsigned char,
		unsigned short,
		unsigned int,
		unsigned long,
		unsigned long long
	>;

// is_standard_integer
template <typename T>
using is_standard_integer =
	hamon::disjunction<
		hamon::detail::is_standard_signed_integer<T>,
		hamon::detail::is_standard_unsigned_integer<T>
	>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_UTILITY_DETAIL_IS_STANDARD_INTEGER_HPP
