/**
 *	@file	stringize.hpp
 *
 *	@brief	HAMON_PP_STRINGIZE の定義
 */

#ifndef HAMON_PREPROCESSOR_STRINGIZE_HPP
#define HAMON_PREPROCESSOR_STRINGIZE_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# /* HAMON_PP_STRINGIZE */
#
# if HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC()
#    define HAMON_PP_STRINGIZE(text) HAMON_PP_STRINGIZE_A((text))
#    define HAMON_PP_STRINGIZE_A(arg) HAMON_PP_STRINGIZE_I arg
# elif HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
#    define HAMON_PP_STRINGIZE(text) HAMON_PP_STRINGIZE_OO((text))
#    define HAMON_PP_STRINGIZE_OO(par) HAMON_PP_STRINGIZE_I ## par
# else
#    define HAMON_PP_STRINGIZE(text) HAMON_PP_STRINGIZE_I(text)
# endif
#
# define HAMON_PP_STRINGIZE_I(text) #text
#
#endif // HAMON_PREPROCESSOR_STRINGIZE_HPP
