/**
 *	@file	is_single_return.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#define HAMON_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# /* HAMON_PP_TUPLE_IS_SINGLE_RETURN */
#
# if HAMON_PP_VARIADICS && HAMON_PP_VARIADICS_MSVC
# include <hamon/preprocessor/control/iif.hpp>
# include <hamon/preprocessor/facilities/is_1.hpp>
# include <hamon/preprocessor/tuple/size.hpp>
# define HAMON_PP_TUPLE_IS_SINGLE_RETURN(sr,nsr,tuple)	\
	HAMON_PP_IIF(HAMON_PP_IS_1(HAMON_PP_TUPLE_SIZE(tuple)),sr,nsr) \
	/**/
# endif /* HAMON_PP_VARIADICS && HAMON_PP_VARIADICS_MSVC */
#
#endif // HAMON_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
