/**
 *	@file	is_empty_variadic.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
#define HAMON_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP

# include <hamon/preprocessor/config/config.hpp>

# if HAMON_PP_VARIADICS

# include <hamon/preprocessor/punctuation/is_begin_parens.hpp>
# include <hamon/preprocessor/facilities/detail/is_empty.hpp>

#if HAMON_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define HAMON_PP_IS_EMPTY(param)       \
    HAMON_PP_DETAIL_IS_EMPTY_IIF       \
      (                                \
      HAMON_PP_IS_BEGIN_PARENS         \
        (                              \
        param                          \
        )                              \
      )                                \
      (                                \
      HAMON_PP_IS_EMPTY_ZERO,          \
      HAMON_PP_DETAIL_IS_EMPTY_PROCESS \
      )                                \
    (param)                            \
/**/
#define HAMON_PP_IS_EMPTY_ZERO(param) 0

# else

#define HAMON_PP_IS_EMPTY(...)         \
    HAMON_PP_DETAIL_IS_EMPTY_IIF       \
      (                                \
      HAMON_PP_IS_BEGIN_PARENS         \
        (                              \
        __VA_ARGS__                    \
        )                              \
      )                                \
      (                                \
      HAMON_PP_IS_EMPTY_ZERO,          \
      HAMON_PP_DETAIL_IS_EMPTY_PROCESS \
      )                                \
    (__VA_ARGS__)                      \
/**/
#define HAMON_PP_IS_EMPTY_ZERO(...) 0

# endif /* HAMON_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
# endif /* HAMON_PP_VARIADICS */

#endif // HAMON_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
