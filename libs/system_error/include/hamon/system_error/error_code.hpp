/**
 *	@file	error_code.hpp
 *
 *	@brief	error_code の定義
 */

#ifndef HAMON_SYSTEM_ERROR_ERROR_CODE_HPP
#define HAMON_SYSTEM_ERROR_ERROR_CODE_HPP

#include <hamon/system_error/config.hpp>

#if defined(HAMON_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace hamon
{

using std::error_code;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_SYSTEM_ERROR_ERROR_CODE_HPP
