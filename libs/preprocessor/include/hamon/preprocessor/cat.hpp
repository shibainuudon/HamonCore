/**
 *	@file	cat.hpp
 *
 *	@brief	HAMON_PP_CAT の定義
 */

#ifndef HAMON_PREPROCESSOR_CAT_HPP
#define HAMON_PREPROCESSOR_CAT_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# /* HAMON_PP_CAT */
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
#    define HAMON_PP_CAT(a, b) HAMON_PP_CAT_I(a, b)
# else
#    define HAMON_PP_CAT(a, b) HAMON_PP_CAT_OO((a, b))
#    define HAMON_PP_CAT_OO(par) HAMON_PP_CAT_I ## par
# endif
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC()
#    define HAMON_PP_CAT_I(a, b) a ## b
# else
#    define HAMON_PP_CAT_I(a, b) HAMON_PP_CAT_II(~, a ## b)
#    define HAMON_PP_CAT_II(p, res) res
# endif
#
#endif // HAMON_PREPROCESSOR_CAT_HPP
