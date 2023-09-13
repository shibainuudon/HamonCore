/**
 *	@file	invalid_argument.hpp
 *
 *	@brief	invalid_argument の定義
 */

#ifndef HAMON_STDEXCEPT_INVALID_ARGUMENT_HPP
#define HAMON_STDEXCEPT_INVALID_ARGUMENT_HPP

#include <hamon/config.hpp>
#include <stdexcept>
#include <cstdlib>		// std::abort

namespace hamon
{

using std::invalid_argument;

namespace detail
{

HAMON_NORETURN inline void
throw_invalid_argument(char const* msg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::invalid_argument(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STDEXCEPT_INVALID_ARGUMENT_HPP
