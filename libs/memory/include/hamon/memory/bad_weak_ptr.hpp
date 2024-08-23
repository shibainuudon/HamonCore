/**
 *	@file	bad_weak_ptr.hpp
 *
 *	@brief	bad_weak_ptr の定義
 */

#ifndef HAMON_MEMORY_BAD_WEAK_PTR_HPP
#define HAMON_MEMORY_BAD_WEAK_PTR_HPP

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>
#include <memory>

namespace hamon
{

// 20.3.2.1 Class bad_weak_ptr[util.smartptr.weak.bad]
using std::bad_weak_ptr;

namespace detail
{

HAMON_NORETURN inline void
throw_bad_weak_ptr()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::bad_weak_ptr();
#else
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_BAD_WEAK_PTR_HPP
