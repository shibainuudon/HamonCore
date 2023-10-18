/**
 *	@file	length_error.hpp
 *
 *	@brief	length_error の定義
 */

#ifndef HAMON_STDEXCEPT_LENGTH_ERROR_HPP
#define HAMON_STDEXCEPT_LENGTH_ERROR_HPP

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>
#include <stdexcept>

namespace hamon
{

using std::length_error;

namespace detail
{

HAMON_NORETURN inline void
throw_length_error(char const* msg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::length_error(msg);
#else
	(void)msg;
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STDEXCEPT_LENGTH_ERROR_HPP
