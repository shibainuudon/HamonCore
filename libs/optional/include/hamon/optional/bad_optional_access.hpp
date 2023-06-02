/**
 *	@file	bad_optional_access.hpp
 *
 *	@brief	bad_optional_access の定義
 */

#ifndef HAMON_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
#define HAMON_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP

#include <hamon/optional/config.hpp>

#if defined(HAMON_USE_STD_OPTIONAL)

#include <optional>

namespace hamon
{

using std::bad_optional_access;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <exception>

namespace hamon
{

// [optional.bad.access], class bad_optional_access
class bad_optional_access : public std::exception
{
public:
	bad_optional_access() = default;
	virtual ~bad_optional_access() = default;

	char const* what() const HAMON_NOEXCEPT override
	{
		// [optional.bad.access]/2
		return "bad optional access";
	}
};

}	// namespace hamon

#endif

#endif // HAMON_OPTIONAL_BAD_OPTIONAL_ACCESS_HPP
