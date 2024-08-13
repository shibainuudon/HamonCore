/**
 *	@file	bad_array_new_length.hpp
 *
 *	@brief	bad_array_new_length の定義
 */

#ifndef HAMON_NEW_BAD_ARRAY_NEW_LENGTH_HPP
#define HAMON_NEW_BAD_ARRAY_NEW_LENGTH_HPP

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>
#include <new>

namespace hamon
{

using std::bad_array_new_length;

namespace detail
{

HAMON_NORETURN inline void
throw_bad_array_new_length()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::bad_array_new_length();
#else
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_NEW_BAD_ARRAY_NEW_LENGTH_HPP
