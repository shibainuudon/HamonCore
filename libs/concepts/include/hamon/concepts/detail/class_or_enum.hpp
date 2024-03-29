﻿/**
 *	@file	class_or_enum.hpp
 *
 *	@brief	class_or_enum の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
#define HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/is_union.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept class_or_enum =
	hamon::is_class<T>::value ||
	hamon::is_union<T>::value ||
	hamon::is_enum<T>::value;

#else

template <typename T>
using class_or_enum = hamon::disjunction<
	hamon::is_class<T>,
	hamon::is_union<T>,
	hamon::is_enum<T>
>;

#endif

template <typename T>
using class_or_enum_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::class_or_enum<T>>;
#else
	hamon::detail::class_or_enum<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CLASS_OR_ENUM_HPP
