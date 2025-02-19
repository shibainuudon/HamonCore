/**
 *	@file	runtime_error.hpp
 *
 *	@brief	runtime_error の定義
 */

#ifndef HAMON_STDEXCEPT_RUNTIME_ERROR_HPP
#define HAMON_STDEXCEPT_RUNTIME_ERROR_HPP

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>
#include <stdexcept>

namespace hamon
{

using std::runtime_error;

namespace detail
{

HAMON_NORETURN inline void
throw_runtime_error(char const* msg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::runtime_error(msg);
#else
	(void)msg;
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STDEXCEPT_RUNTIME_ERROR_HPP
