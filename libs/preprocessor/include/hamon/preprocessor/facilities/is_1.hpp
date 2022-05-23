/**
 *	@file	is_1.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_FACILITIES_IS_1_HPP
#define HAMON_PREPROCESSOR_FACILITIES_IS_1_HPP
#
# include <hamon/preprocessor/cat.hpp>
# include <hamon/preprocessor/facilities/is_empty.hpp>
#
# /* HAMON_PP_IS_1 */
#
# define HAMON_PP_IS_1(x) HAMON_PP_IS_EMPTY(HAMON_PP_CAT(HAMON_PP_IS_1_HELPER_, x))
# define HAMON_PP_IS_1_HELPER_1
#
#endif // HAMON_PREPROCESSOR_FACILITIES_IS_1_HPP
