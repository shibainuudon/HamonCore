/**
 *	@file	class_or_enum.hpp
 *
 *	@brief	class_or_enum の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
#define HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP

#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/is_union.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CONCEPT_OR_BOOL class_or_enum =
	hamon::is_class<T>::value ||
	hamon::is_union<T>::value ||
	hamon::is_enum<T>::value;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
