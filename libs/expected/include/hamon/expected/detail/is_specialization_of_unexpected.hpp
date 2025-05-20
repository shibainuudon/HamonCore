/**
 *	@file	is_specialization_of_unexpected.hpp
 *
 *	@brief	is_specialization_of_unexpected の定義
 */

#ifndef HAMON_EXPECTED_DETAIL_IS_SPECIALIZATION_OF_UNEXPECTED_HPP
#define HAMON_EXPECTED_DETAIL_IS_SPECIALIZATION_OF_UNEXPECTED_HPP

#include <hamon/expected/unexpected_fwd.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_unexpected
	: public hamon::false_type {};

template <typename E>
struct is_specialization_of_unexpected<hamon::unexpected<E>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_EXPECTED_DETAIL_IS_SPECIALIZATION_OF_UNEXPECTED_HPP
