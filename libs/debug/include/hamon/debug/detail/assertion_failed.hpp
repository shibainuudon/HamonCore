/**
 *	@file	assertion_failed.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_ASSERTION_FAILED_HPP
#define HAMON_DEBUG_DETAIL_ASSERTION_FAILED_HPP

#include <hamon/debug/assertion_handler.hpp>
#include <sstream>

namespace hamon
{

namespace debug
{

namespace detail
{

template <typename Expr>
inline bool
assertion_failed(
	char const* file_name,
	int line_number,
	char const* function_name,
	char const* expr_str,
	Expr const& expr,
	char const* msg)
{
	std::stringstream ss;
	ss << expr;

	hamon::debug::get_assertion_handler()(
		assertion_info(
			file_name,
			line_number,
			function_name,
			expr_str,
			ss.str().c_str(),
			msg));

	return false;
}

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_ASSERTION_FAILED_HPP
