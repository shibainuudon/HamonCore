/**
 *	@file	assertion_failed.hpp
 *
 *	@brief
 */

#ifndef HAMON_POWER_ASSERT_DETAIL_ASSERTION_FAILED_HPP
#define HAMON_POWER_ASSERT_DETAIL_ASSERTION_FAILED_HPP

#include <hamon/power_assert/assertion_handler.hpp>
#include <hamon/sstream/stringstream.hpp>

namespace hamon
{
namespace power_assert
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
	hamon::stringstream ss;
	ss << expr;

	hamon::power_assert::get_assertion_handler()(
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
}	// namespace power_assert
}	// namespace hamon

#endif // HAMON_POWER_ASSERT_DETAIL_ASSERTION_FAILED_HPP
