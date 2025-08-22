/**
 *	@file	format_error.hpp
 *
 *	@brief	format_error の定義
 */

#ifndef HAMON_FORMAT_FORMAT_ERROR_HPP
#define HAMON_FORMAT_FORMAT_ERROR_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_error;

}	// namespace hamon

#else

#include <hamon/cstdlib/abort.hpp>
#include <hamon/config.hpp>
#include <stdexcept>
#include <string>

namespace hamon
{

// 28.5.10 Class format_error[format.error]

class format_error : public std::runtime_error
{
public:
	/*constexpr*/ explicit
	format_error(const std::string& what_arg)
		: runtime_error(what_arg)
	{}

	/*constexpr*/ explicit
	format_error(const char* what_arg)
		: runtime_error(what_arg)
	{}
};

namespace detail
{

HAMON_NORETURN inline void
throw_format_error(char const* msg)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	throw hamon::format_error(msg);
#else
	(void)msg;
	hamon::abort();
#endif
}

}	// namespace detail

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_ERROR_HPP
