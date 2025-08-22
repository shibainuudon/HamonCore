/**
 *	@file	is_unsigned_integer.hpp
 *
 *	@brief	is_unsigned_integer の定義
 */

#ifndef HAMON_FORMAT_DETAIL_IS_UNSIGNED_INTEGER_HPP
#define HAMON_FORMAT_DETAIL_IS_UNSIGNED_INTEGER_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon
{

namespace detail
{

// TODO: 別の場所で定義してもいいかも

// 6.9.2 Fundamental types[basic.fundamental]

// [basic.fundamental]/2
template <typename T>
using is_unsigned_integer = hamon::disjunction<
	hamon::is_same<T, unsigned char>,
	hamon::is_same<T, unsigned short int>,
	hamon::is_same<T, unsigned int>,
	hamon::is_same<T, unsigned long int>,
	hamon::is_same<T, unsigned long long int>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_IS_UNSIGNED_INTEGER_HPP
