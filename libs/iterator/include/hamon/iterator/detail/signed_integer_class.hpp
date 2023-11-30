/**
 *	@file	signed_integer_class.hpp
 *
 *	@brief	signed_integer_class の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_SIGNED_INTEGER_CLASS_HPP
#define HAMON_ITERATOR_DETAIL_SIGNED_INTEGER_CLASS_HPP

#include <hamon/detail/max_diff_type.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

// ある型を is_signed_integer_like でtrueとしたい場合は、このクラステンプレートを特殊化する
template <typename T>
struct signed_integer_class
	: public hamon::false_type {};

template <>
struct signed_integer_class<hamon::detail::max_diff_type>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_SIGNED_INTEGER_CLASS_HPP
