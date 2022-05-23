/**
 *	@file	overload.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#define HAMON_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <hamon/preprocessor/cat.hpp>
# include <hamon/preprocessor/variadic/size.hpp>
#
# /* HAMON_PP_OVERLOAD */
#
# if HAMON_PP_VARIADICS
#    define HAMON_PP_OVERLOAD(prefix, ...) HAMON_PP_CAT(prefix, HAMON_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
#endif // HAMON_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
