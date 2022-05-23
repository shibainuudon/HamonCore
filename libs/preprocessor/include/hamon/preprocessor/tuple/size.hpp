/**
 *	@file	size.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_TUPLE_SIZE_HPP
#define HAMON_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <hamon/preprocessor/cat.hpp>
# include <hamon/preprocessor/config/config.hpp>
# include <hamon/preprocessor/variadic/size.hpp>
#
# if HAMON_PP_VARIADICS
#    if HAMON_PP_VARIADICS_MSVC
#        define HAMON_PP_TUPLE_SIZE(tuple) HAMON_PP_CAT(HAMON_PP_VARIADIC_SIZE tuple,)
#    else
#        define HAMON_PP_TUPLE_SIZE(tuple) HAMON_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
#endif // HAMON_PREPROCESSOR_TUPLE_SIZE_HPP
