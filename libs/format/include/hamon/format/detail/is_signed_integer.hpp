/**
 *	@file	is_signed_integer.hpp
 *
 *	@brief	is_signed_integer の定義
 */

#ifndef HAMON_FORMAT_DETAIL_IS_SIGNED_INTEGER_HPP
#define HAMON_FORMAT_DETAIL_IS_SIGNED_INTEGER_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon
{

namespace detail
{

// TODO: 別の場所で定義してもいいかも

// 6.9.2 Fundamental types[basic.fundamental]

// [basic.fundamental]/1
template <typename T>
using is_signed_integer = hamon::disjunction<
	hamon::is_same<T, signed char>,
	hamon::is_same<T, short int>,
	hamon::is_same<T, int>,
	hamon::is_same<T, long int>,
	hamon::is_same<T, long long int>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_IS_SIGNED_INTEGER_HPP
