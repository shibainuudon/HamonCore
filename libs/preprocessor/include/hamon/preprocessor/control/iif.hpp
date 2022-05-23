/**
 *	@file	iif.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_CONTROL_IIF_HPP
#define HAMON_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
#    define HAMON_PP_IIF(bit, t, f) HAMON_PP_IIF_I(bit, t, f)
# else
#    define HAMON_PP_IIF(bit, t, f) HAMON_PP_IIF_OO((bit, t, f))
#    define HAMON_PP_IIF_OO(par) HAMON_PP_IIF_I ## par
# endif
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC()
#    define HAMON_PP_IIF_I(bit, t, f) HAMON_PP_IIF_ ## bit(t, f)
# else
#    define HAMON_PP_IIF_I(bit, t, f) HAMON_PP_IIF_II(HAMON_PP_IIF_ ## bit(t, f))
#    define HAMON_PP_IIF_II(id) id
# endif
#
# define HAMON_PP_IIF_0(t, f) f
# define HAMON_PP_IIF_1(t, f) t
#
#endif // HAMON_PREPROCESSOR_CONTROL_IIF_HPP
