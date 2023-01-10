/**
 *	@file	assertion_check.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_ASSERTION_CHECK_HPP
#define HAMON_DEBUG_DETAIL_ASSERTION_CHECK_HPP

#include <hamon/debug/detail/assertion_failed.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace debug
{

namespace detail
{

template <typename Expr>
inline HAMON_CONSTEXPR bool
assertion_check(
	bool cond,
	char const* file_name,
	int line_number,
	char const* function_name,
	char const* expr_str,
	Expr const& expr,
	char const* msg)
{
	return cond ? true :
		hamon::debug::detail::assertion_failed(
			file_name,
			line_number,
			function_name,
			expr_str,
			expr,
			msg);
}

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_ASSERTION_CHECK_HPP
