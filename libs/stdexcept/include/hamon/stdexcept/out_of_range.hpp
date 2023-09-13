/**
 *	@file	out_of_range.hpp
 *
 *	@brief	out_of_range の定義
 */

#ifndef HAMON_STDEXCEPT_OUT_OF_RANGE_HPP
#define HAMON_STDEXCEPT_OUT_OF_RANGE_HPP

#include <hamon/config.hpp>
#include <stdexcept>
#include <cstdlib>		// std::abort

namespace hamon
{

using std::out_of_range;

namespace detail
{

HAMON_NORETURN inline void
throw_out_of_range(char const* msg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::out_of_range(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STDEXCEPT_OUT_OF_RANGE_HPP
