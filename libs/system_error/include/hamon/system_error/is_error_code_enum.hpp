/**
 *	@file	is_error_code_enum.hpp
 *
 *	@brief	is_error_code_enum の定義
 */

#ifndef HAMON_SYSTEM_ERROR_IS_ERROR_CODE_ENUM_HPP
#define HAMON_SYSTEM_ERROR_IS_ERROR_CODE_ENUM_HPP

#include <hamon/system_error/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace hamon
{

using std::is_error_code_enum;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_error_code_enum_v = hamon::is_error_code_enum<T>::value;

}	// namespace hamon

#endif

#endif // HAMON_SYSTEM_ERROR_IS_ERROR_CODE_ENUM_HPP
