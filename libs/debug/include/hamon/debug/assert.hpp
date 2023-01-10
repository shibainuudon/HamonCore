/**
 *	@file	assert.hpp
 *
 *	@brief
 */

// NO INCLUDE GUARD

#undef HAMON_ASSERT
#undef HAMON_ASSERT_MSG

#if defined(HAMON_DISABLE_ASSERTS)

#	define HAMON_ASSERT(expr)          ((void)0)
#	define HAMON_ASSERT_MSG(expr, msg) ((void)0)

#else

#	include <hamon/debug/detail/seed.hpp>
#	include <hamon/debug/detail/binary_expression.hpp>
#	include <hamon/debug/detail/value_expression.hpp>
#	include <hamon/debug/detail/operators.hpp>
#	include <hamon/debug/detail/assertion_check.hpp>
#	include <hamon/config.hpp>

#	define HAMON_ASSERT(expr)                     \
	HAMON_ASSERT_MSG(expr, "")                    \
	/**/

#	define HAMON_ASSERT_MSG(expr, msg)            \
	((void)hamon::debug::detail::assertion_check( \
		(expr),                                   \
		__FILE__,                                 \
		__LINE__,                                 \
		HAMON_CURRENT_FUNCTION,                   \
		#expr,                                    \
		hamon::debug::detail::seed()->*expr,      \
		msg))                                     \
	/**/

#endif
