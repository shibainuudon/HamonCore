/**
 *	@file	bad_any_cast.hpp
 *
 *	@brief	bad_any_cast の定義
 */

#ifndef HAMON_ANY_BAD_ANY_CAST_HPP
#define HAMON_ANY_BAD_ANY_CAST_HPP

#include <hamon/any/config.hpp>

#if defined(HAMON_USE_STD_ANY)

#include <any>

namespace hamon
{

using std::bad_any_cast;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <cstdlib>	// abort
#include <typeinfo>	// bad_cast

namespace hamon
{

// [any.bad.any.cast], class bad_any_cast
class bad_any_cast : public std::bad_cast
{
public:
	// see [exception] for the specification of the special member functions
	const char* what() const noexcept override
	{
		return "bad any_cast";
	}
};

namespace detail
{

HAMON_NORETURN inline void throw_bad_any_cast()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::bad_any_cast();
#else
	std::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif

#endif // HAMON_ANY_BAD_ANY_CAST_HPP
