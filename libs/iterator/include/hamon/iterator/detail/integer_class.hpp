/**
 *	@file	integer_class.hpp
 *
 *	@brief	integer_class の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_INTEGER_CLASS_HPP
#define HAMON_ITERATOR_DETAIL_INTEGER_CLASS_HPP

#include <hamon/detail/max_diff_type.hpp>
#include <hamon/detail/max_size_type.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

// ある型を is_integer_like でtrueとしたい場合は、このクラステンプレートを特殊化する
template <typename T>
struct integer_class
	: public hamon::false_type {};

template <>
struct integer_class<hamon::detail::max_diff_type>
	: public hamon::true_type {};

template <>
struct integer_class<hamon::detail::max_size_type>
	: public hamon::true_type {};

#if defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_HAS_CXX20_CONCEPTS)

template <>
struct integer_class<std::_Signed128>
	: public hamon::true_type {};

template <>
struct integer_class<std::_Unsigned128>
	: public hamon::true_type {};

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_INTEGER_CLASS_HPP
