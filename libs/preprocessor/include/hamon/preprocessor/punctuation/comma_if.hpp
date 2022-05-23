/**
 *	@file	comma_if.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#define HAMON_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <hamon/preprocessor/config/config.hpp>
# include <hamon/preprocessor/control/if.hpp>
# include <hamon/preprocessor/facilities/empty.hpp>
# include <hamon/preprocessor/punctuation/comma.hpp>
#
# /* HAMON_PP_COMMA_IF */
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_EDG()
#    define HAMON_PP_COMMA_IF(cond) HAMON_PP_IF(cond, HAMON_PP_COMMA, HAMON_PP_EMPTY)()
# else
#    define HAMON_PP_COMMA_IF(cond) HAMON_PP_COMMA_IF_I(cond)
#    define HAMON_PP_COMMA_IF_I(cond) HAMON_PP_IF(cond, HAMON_PP_COMMA, HAMON_PP_EMPTY)()
# endif
#
#endif // HAMON_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
