/**
 *	@file	is_specialization_of_pair.hpp
 *
 *	@brief	is_specialization_of_pair の定義
 */

#ifndef HAMON_PAIR_DETAIL_IS_SPECIALIZATION_OF_PAIR_HPP
#define HAMON_PAIR_DETAIL_IS_SPECIALIZATION_OF_PAIR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <utility>
#endif

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_pair
	: public hamon::false_type {};

#if !defined(HAMON_NO_STD)
template <typename T, typename U>
struct is_specialization_of_pair<std::pair<T, U>>
	: public hamon::true_type {};
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_PAIR_DETAIL_IS_SPECIALIZATION_OF_PAIR_HPP
