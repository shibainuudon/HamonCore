/**
 *	@file	if.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_CONTROL_IF_HPP
#define HAMON_PREPROCESSOR_CONTROL_IF_HPP
#
# include <hamon/preprocessor/config/config.hpp>
# include <hamon/preprocessor/control/iif.hpp>
# include <hamon/preprocessor/logical/bool.hpp>
#
# /* HAMON_PP_IF */
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_EDG()
#    define HAMON_PP_IF(cond, t, f) HAMON_PP_IIF(HAMON_PP_BOOL(cond), t, f)
# else
#    define HAMON_PP_IF(cond, t, f) HAMON_PP_IF_I(cond, t, f)
#    define HAMON_PP_IF_I(cond, t, f) HAMON_PP_IIF(HAMON_PP_BOOL(cond), t, f)
# endif
#
#endif // HAMON_PREPROCESSOR_CONTROL_IF_HPP
