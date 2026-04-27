/**
 *	@file	is_constant_evaluated.hpp
 *
 *	@brief	is_constant_evaluated の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP
#define HAMON_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_is_constant_evaluated) && (__cpp_lib_is_constant_evaluated >= 201811)

using std::is_constant_evaluated;

#else

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
is_constant_evaluated() HAMON_NOEXCEPT
{
	return __builtin_is_constant_evaluated();
}

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_CONSTANT_EVALUATED_HPP
