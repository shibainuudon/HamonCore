/**
 *	@file	expand.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_FACILITIES_EXPAND_HPP
#define HAMON_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC() && ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_DMC()
#    define HAMON_PP_EXPAND(x) HAMON_PP_EXPAND_I(x)
# else
#    define HAMON_PP_EXPAND(x) HAMON_PP_EXPAND_OO((x))
#    define HAMON_PP_EXPAND_OO(par) HAMON_PP_EXPAND_I ## par
# endif
#
# define HAMON_PP_EXPAND_I(x) x
#
#endif // HAMON_PREPROCESSOR_FACILITIES_EXPAND_HPP
