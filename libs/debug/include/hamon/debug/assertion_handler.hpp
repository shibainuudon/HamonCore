/**
 *	@file	assertion_handler.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_ASSERTION_HANDLER_HPP
#define HAMON_DEBUG_ASSERTION_HANDLER_HPP

#include <hamon/debug/assertion_info.hpp>
#include <hamon/cstdlib/abort.hpp>
#include <hamon/ostream/endl.hpp>
#include <iostream>

namespace hamon
{

namespace debug
{

/**
 *	assertion_handler
 */
using assertion_handler = void (*)(assertion_info const&);

namespace detail
{

inline void default_assertion_handler(assertion_info const& info)
{
	std::cout
		<< info.file_name << "(" << info.line_number << "): error : "
		<< info.function_name      << hamon::endl
		<< "Assertion failed:"     << hamon::endl
		<< info.expr_str           << hamon::endl
		<< info.evaluated_expr_str << hamon::endl
		<< info.msg                << hamon::endl;

	hamon::abort();
}

inline assertion_handler& assertion_handler_instance(void)
{
	static assertion_handler s_assertion_handler = default_assertion_handler;
	return s_assertion_handler;
}

}	// namespace detail

/**
 *	get_assertion_handler
 */
inline assertion_handler const& get_assertion_handler(void)
{
	return detail::assertion_handler_instance();
}

/**
 *	set_assertion_handler
 */
inline void set_assertion_handler(assertion_handler const& handler)
{
	detail::assertion_handler_instance() = handler;
}

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_ASSERTION_HANDLER_HPP
