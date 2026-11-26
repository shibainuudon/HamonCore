/**
 *	@file	macro.hpp
 *
 *	@brief	HAMON_POWER_ASSERT マクロを定義
 */

// NO INCLUDE GUARD

#undef HAMON_POWER_ASSERT
#undef HAMON_POWER_ASSERT_MSG

#if defined(HAMON_DISABLE_POWER_ASSERTS)

#	define HAMON_POWER_ASSERT(expr)          ((void)0)
#	define HAMON_POWER_ASSERT_MSG(expr, msg) ((void)0)

#else

#	include <hamon/power_assert/detail/seed.hpp>
#	include <hamon/power_assert/detail/binary_expression.hpp>
#	include <hamon/power_assert/detail/value_expression.hpp>
#	include <hamon/power_assert/detail/operators.hpp>
#	include <hamon/power_assert/detail/assertion_check.hpp>
#	include <hamon/config.hpp>

#	define HAMON_POWER_ASSERT(expr)                     \
	HAMON_POWER_ASSERT_MSG(expr, "")                    \
	/**/

#	define HAMON_POWER_ASSERT_MSG(expr, msg)            \
	((void)hamon::power_assert::detail::assertion_check( \
		(expr),                                   \
		__FILE__,                                 \
		__LINE__,                                 \
		HAMON_CURRENT_FUNCTION,                   \
		#expr,                                    \
		hamon::power_assert::detail::seed()->*expr,      \
		msg))                                     \
	/**/

#endif
