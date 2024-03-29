﻿/**
 *	@file	is_begin_parens.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_PUNCTUATION_DETAIL_IS_BEGIN_PARENS_HPP
#define HAMON_PREPROCESSOR_PUNCTUATION_DETAIL_IS_BEGIN_PARENS_HPP

#if HAMON_PP_VARIADICS_MSVC

#include <hamon/preprocessor/facilities/empty.hpp>

#define HAMON_PP_DETAIL_VD_IBP_CAT(a, b) HAMON_PP_DETAIL_VD_IBP_CAT_I(a, b)
#define HAMON_PP_DETAIL_VD_IBP_CAT_I(a, b) HAMON_PP_DETAIL_VD_IBP_CAT_II(a ## b)
#define HAMON_PP_DETAIL_VD_IBP_CAT_II(res) res

#define HAMON_PP_DETAIL_IBP_SPLIT(i, ...) \
    HAMON_PP_DETAIL_VD_IBP_CAT(HAMON_PP_DETAIL_IBP_PRIMITIVE_CAT(HAMON_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__),HAMON_PP_EMPTY()) \
/**/

#define HAMON_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1 1

#else

#define HAMON_PP_DETAIL_IBP_SPLIT(i, ...) \
    HAMON_PP_DETAIL_IBP_PRIMITIVE_CAT(HAMON_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__) \
/**/

#define HAMON_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1

#endif /* HAMON_PP_VARIADICS_MSVC */

#define HAMON_PP_DETAIL_IBP_SPLIT_0(a, ...) a
#define HAMON_PP_DETAIL_IBP_SPLIT_1(a, ...) __VA_ARGS__

#define HAMON_PP_DETAIL_IBP_CAT(a, ...) HAMON_PP_DETAIL_IBP_PRIMITIVE_CAT(a,__VA_ARGS__)
#define HAMON_PP_DETAIL_IBP_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define HAMON_PP_DETAIL_IBP_IS_VARIADIC_R_1 1,
#define HAMON_PP_DETAIL_IBP_IS_VARIADIC_R_HAMON_PP_DETAIL_IBP_IS_VARIADIC_C 0,

#endif // HAMON_PREPROCESSOR_PUNCTUATION_DETAIL_IS_BEGIN_PARENS_HPP
