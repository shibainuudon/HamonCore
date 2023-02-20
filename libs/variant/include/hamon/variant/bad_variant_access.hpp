/**
 *	@file	bad_variant_access.hpp
 *
 *	@brief	bad_variant_access の定義
 */

#ifndef HAMON_VARIANT_BAD_VARIANT_ACCESS_HPP
#define HAMON_VARIANT_BAD_VARIANT_ACCESS_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::bad_variant_access;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <exception>
#include <cstdlib>

namespace hamon
{

// [variant.bad.access], class bad_variant_access
class bad_variant_access : public std::exception
{
public:
	char const* what() const HAMON_NOEXCEPT override
	{
		return "bad variant access";
	}
};

HAMON_NORETURN inline
void throw_bad_variant_access()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw bad_variant_access();
#else
	std::abort();
#endif
}

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_BAD_VARIANT_ACCESS_HPP
