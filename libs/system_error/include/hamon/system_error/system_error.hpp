/**
 *	@file	system_error.hpp
 *
 *	@brief	system_error の定義
 */

#ifndef HAMON_SYSTEM_ERROR_SYSTEM_ERROR_HPP
#define HAMON_SYSTEM_ERROR_SYSTEM_ERROR_HPP

#include <hamon/system_error/config.hpp>

#if defined(HAMON_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace hamon
{

using std::system_error;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#include <hamon/system_error/error_code.hpp>
#include <hamon/system_error/error_category.hpp>
#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_NORETURN inline void
throw_system_error(hamon::error_code ec, const char* what_arg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::system_error(ec, what_arg);
#else
	(void)ec;
	(void)what_arg;
	hamon::abort();
#endif
}

HAMON_NORETURN inline void
throw_system_error(hamon::error_code ec)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::system_error(ec);
#else
	(void)ec;
	hamon::abort();
#endif
}

HAMON_NORETURN inline void
throw_system_error(int ev, hamon::error_category const& cat, char const* what_arg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::system_error(ev, cat, what_arg);
#else
	(void)ev;
	(void)cat;
	(void)what_arg;
	hamon::abort();
#endif
}

HAMON_NORETURN inline void
throw_system_error(int ev, hamon::error_category const& cat)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::system_error(ev, cat);
#else
	(void)ev;
	(void)cat;
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SYSTEM_ERROR_SYSTEM_ERROR_HPP
