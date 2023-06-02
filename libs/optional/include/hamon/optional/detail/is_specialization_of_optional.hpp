/**
 *	@file	is_specialization_of_optional.hpp
 *
 *	@brief	is_specialization_of_optional の定義
 */

#ifndef HAMON_OPTIONAL_DETAIL_IS_SPECIALIZATION_OF_OPTIONAL_HPP
#define HAMON_OPTIONAL_DETAIL_IS_SPECIALIZATION_OF_OPTIONAL_HPP

#include <hamon/optional/optional_fwd.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace optional_detail
{

template <typename T>
struct is_specialization_of_optional
	: public hamon::false_type {};

template <typename T>
struct is_specialization_of_optional<hamon::optional<T>>
	: public hamon::true_type {};

}	// namespace optional_detail

}	// namespace hamon

#endif // HAMON_OPTIONAL_DETAIL_IS_SPECIALIZATION_OF_OPTIONAL_HPP
