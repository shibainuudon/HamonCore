/**
 *	@file	is_initializer_list.hpp
 *
 *	@brief	is_initializer_list の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_DETAIL_IS_INITIALIZER_LIST_HPP
#define HAMON_RANGES_CONCEPTS_DETAIL_IS_INITIALIZER_LIST_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <initializer_list>

namespace hamon {
namespace ranges {
namespace detail {

// [range.refinements]/5

template <typename T>
struct is_initializer_list : public hamon::false_type {};

template <typename T>
struct is_initializer_list<std::initializer_list<T>> : public hamon::true_type {};

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_DETAIL_IS_INITIALIZER_LIST_HPP
