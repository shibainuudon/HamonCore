/**
 *	@file	assertion_check.hpp
 *
 *	@brief
 */

#ifndef HAMON_POWER_ASSERT_DETAIL_ASSERTION_CHECK_HPP
#define HAMON_POWER_ASSERT_DETAIL_ASSERTION_CHECK_HPP

#include <hamon/power_assert/detail/assertion_failed.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace power_assert
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
		hamon::power_assert::detail::assertion_failed(
			file_name,
			line_number,
			function_name,
			expr_str,
			expr,
			msg);
}

}	// namespace detail
}	// namespace power_assert
}	// namespace hamon

#endif // HAMON_POWER_ASSERT_DETAIL_ASSERTION_CHECK_HPP
