/**
 *	@file	is_empty.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_FACILITIES_DETAIL_IS_EMPTY_HPP
#define HAMON_PREPROCESSOR_FACILITIES_DETAIL_IS_EMPTY_HPP

#include <hamon/preprocessor/punctuation/is_begin_parens.hpp>

#if HAMON_PP_VARIADICS_MSVC

# pragma warning(once:4002)

#define HAMON_PP_DETAIL_IS_EMPTY_IIF_0(t, b) b
#define HAMON_PP_DETAIL_IS_EMPTY_IIF_1(t, b) t

#else

#define HAMON_PP_DETAIL_IS_EMPTY_IIF_0(t, ...) __VA_ARGS__
#define HAMON_PP_DETAIL_IS_EMPTY_IIF_1(t, ...) t

#endif

#if HAMON_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define HAMON_PP_DETAIL_IS_EMPTY_PROCESS(param)          \
	HAMON_PP_IS_BEGIN_PARENS                             \
    	(                                                \
        HAMON_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C param () \
        )                                                \
/**/

#else

#define HAMON_PP_DETAIL_IS_EMPTY_PROCESS(...)                  \
	HAMON_PP_IS_BEGIN_PARENS                                   \
        (                                                      \
        HAMON_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        )                                                      \
/**/

#endif

#define HAMON_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(a, b) a ## b
#define HAMON_PP_DETAIL_IS_EMPTY_IIF(bit) HAMON_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(HAMON_PP_DETAIL_IS_EMPTY_IIF_,bit)
#define HAMON_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C(...) ()

#endif // HAMON_PREPROCESSOR_FACILITIES_DETAIL_IS_EMPTY_HPP
