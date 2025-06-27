/**
 *	@file	make_error_condition.hpp
 *
 *	@brief	make_error_condition の定義
 */

#ifndef HAMON_SYSTEM_ERROR_MAKE_ERROR_CONDITION_HPP
#define HAMON_SYSTEM_ERROR_MAKE_ERROR_CONDITION_HPP

#include <hamon/system_error/config.hpp>

#if defined(HAMON_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace hamon
{

using std::make_error_condition;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_SYSTEM_ERROR_MAKE_ERROR_CONDITION_HPP
