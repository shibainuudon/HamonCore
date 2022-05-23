/**
 *	@file	bool_constant.hpp
 *
 *	@brief	bool_constant の定義
 */

#ifndef HAMON_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define HAMON_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_bool_constant) && (__cpp_lib_bool_constant >= 201505)

using std::bool_constant;

#else

template <bool B>
using bool_constant = std::integral_constant<bool, B>;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_BOOL_CONSTANT_HPP
