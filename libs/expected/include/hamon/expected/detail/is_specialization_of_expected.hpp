/**
 *	@file	is_specialization_of_expected.hpp
 *
 *	@brief	is_specialization_of_expected の定義
 */

#ifndef HAMON_EXPECTED_DETAIL_IS_SPECIALIZATION_OF_EXPECTED_HPP
#define HAMON_EXPECTED_DETAIL_IS_SPECIALIZATION_OF_EXPECTED_HPP

#include <hamon/expected/expected_fwd.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_expected
	: public hamon::false_type {};

template <typename T, typename E>
struct is_specialization_of_expected<hamon::expected<T, E>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_EXPECTED_DETAIL_IS_SPECIALIZATION_OF_EXPECTED_HPP
