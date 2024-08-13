/**
 *	@file	bad_alloc.hpp
 *
 *	@brief	bad_alloc の定義
 */

#ifndef HAMON_NEW_BAD_ALLOC_HPP
#define HAMON_NEW_BAD_ALLOC_HPP

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>
#include <new>

namespace hamon
{

using std::bad_alloc;

namespace detail
{

HAMON_NORETURN inline void
throw_bad_alloc()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::bad_alloc();
#else
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_NEW_BAD_ALLOC_HPP
