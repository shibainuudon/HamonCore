/**
 *	@file	is_begin_parens.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_PUNCTUATION_IS_BEGIN_PARENS_HPP
#define HAMON_PREPROCESSOR_PUNCTUATION_IS_BEGIN_PARENS_HPP

# include <hamon/preprocessor/config/config.hpp>

#if HAMON_PP_VARIADICS

#include <hamon/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if HAMON_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define HAMON_PP_IS_BEGIN_PARENS(param)         \
    HAMON_PP_DETAIL_IBP_SPLIT                   \
      (                                         \
      0,                                        \
      HAMON_PP_DETAIL_IBP_CAT                   \
        (                                       \
        HAMON_PP_DETAIL_IBP_IS_VARIADIC_R_,     \
        HAMON_PP_DETAIL_IBP_IS_VARIADIC_C param \
        )                                       \
      )                                         \
/**/

#else

#define HAMON_PP_IS_BEGIN_PARENS(...)                 \
    HAMON_PP_DETAIL_IBP_SPLIT                         \
      (                                               \
      0,                                              \
      HAMON_PP_DETAIL_IBP_CAT                         \
        (                                             \
        HAMON_PP_DETAIL_IBP_IS_VARIADIC_R_,           \
        HAMON_PP_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__ \
        )                                             \
      )                                               \
/**/

#endif /* HAMON_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* HAMON_PP_VARIADICS */

#endif // HAMON_PREPROCESSOR_PUNCTUATION_IS_BEGIN_PARENS_HPP
