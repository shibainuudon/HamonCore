/**
 *	@file	class_or_enum.hpp
 *
 *	@brief	class_or_enum の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
#define HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept class_or_enum =
	std::is_class<T>::value ||
	std::is_union<T>::value ||
	std::is_enum<T>::value;

#else

template <typename T>
using class_or_enum = hamon::disjunction<
	std::is_class<T>,
	std::is_union<T>,
	std::is_enum<T>
>;

#endif

template <typename T>
using class_or_enum_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	std::bool_constant<hamon::detail::class_or_enum<T>>;
#else
	hamon::detail::class_or_enum<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
