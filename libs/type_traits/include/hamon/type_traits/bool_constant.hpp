/**
 *	@file	bool_constant.hpp
 *
 *	@brief	bool_constant の定義
 */

#ifndef HAMON_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define HAMON_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include <hamon/type_traits/integral_constant.hpp>

namespace hamon
{

// [meta.help], helper class

template <bool B>
using bool_constant = hamon::integral_constant<bool, B>;

using true_type  = hamon::bool_constant<true>;
using false_type = hamon::bool_constant<false>;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_BOOL_CONSTANT_HPP
