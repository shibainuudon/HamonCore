/**
 *	@file	make_error_condition.hpp
 *
 *	@brief	make_error_condition の定義
 */

#ifndef HAMON_IOS_MAKE_ERROR_CONDITION_HPP
#define HAMON_IOS_MAKE_ERROR_CONDITION_HPP

#include <ios>

namespace hamon
{

using std::make_error_condition;

#if 0	// TODO
// [error.reporting], error reporting
error_condition make_error_condition(io_errc e) noexcept;
#endif

}	// namespace hamon

#endif // HAMON_IOS_MAKE_ERROR_CONDITION_HPP
