/**
 *	@file	expr_iif.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#define HAMON_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# /* HAMON_PP_EXPR_IIF */
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
#    define HAMON_PP_EXPR_IIF(bit, expr) HAMON_PP_EXPR_IIF_I(bit, expr)
# else
#    define HAMON_PP_EXPR_IIF(bit, expr) HAMON_PP_EXPR_IIF_OO((bit, expr))
#    define HAMON_PP_EXPR_IIF_OO(par) HAMON_PP_EXPR_IIF_I ## par
# endif
#
# define HAMON_PP_EXPR_IIF_I(bit, expr) HAMON_PP_EXPR_IIF_ ## bit(expr)
#
# define HAMON_PP_EXPR_IIF_0(expr)
# define HAMON_PP_EXPR_IIF_1(expr) expr
#
#endif // HAMON_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
