/**
 *	@file	overflow_error.hpp
 *
 *	@brief	overflow_error の定義
 */

#ifndef HAMON_STDEXCEPT_OVERFLOW_ERROR_HPP
#define HAMON_STDEXCEPT_OVERFLOW_ERROR_HPP

#include <hamon/config.hpp>
#include <stdexcept>
#include <cstdlib>		// std::abort

namespace hamon
{

using std::overflow_error;

namespace detail
{

HAMON_NORETURN inline void
throw_overflow_error(char const* msg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::overflow_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STDEXCEPT_OVERFLOW_ERROR_HPP
