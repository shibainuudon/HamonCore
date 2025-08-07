/**
 *	@file	__throw_invalid_option_format_error.hpp
 *
 *	@brief	__throw_invalid_option_format_error の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___THROW_INVALID_OPTION_FORMAT_ERROR_HPP
#define HAMON_FORMAT___FORMAT_SPEC___THROW_INVALID_OPTION_FORMAT_ERROR_HPP

#include <hamon/format/format_error.hpp>
#include <hamon/string.hpp>

namespace hamon
{

namespace __format_spec
{

[[noreturn]] inline void
__throw_invalid_option_format_error(const char* __id, const char* __option)
{
	hamon::detail::throw_format_error(
		(hamon::string("The format specifier for ") + __id + " does not allow the " + __option + " option").c_str());
}

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___THROW_INVALID_OPTION_FORMAT_ERROR_HPP
