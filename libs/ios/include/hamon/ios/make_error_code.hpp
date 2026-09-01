/**
 *	@file	make_error_code.hpp
 *
 *	@brief	make_error_code の定義
 */

#ifndef HAMON_IOS_MAKE_ERROR_CODE_HPP
#define HAMON_IOS_MAKE_ERROR_CODE_HPP

#include <ios>

namespace hamon
{

using std::make_error_code;

#if 0	// TODO
// [error.reporting], error reporting
error_code make_error_code(io_errc e) noexcept;
#endif

}	// namespace hamon

#endif // HAMON_IOS_MAKE_ERROR_CODE_HPP
