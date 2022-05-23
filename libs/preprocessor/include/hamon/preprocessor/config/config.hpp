﻿/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_CONFIG_CONFIG_HPP
#define HAMON_PREPROCESSOR_CONFIG_CONFIG_HPP

# /* HAMON_PP_CONFIG_FLAGS */
#
# define HAMON_PP_CONFIG_STRICT() 0x0001
# define HAMON_PP_CONFIG_IDEAL() 0x0002
#
# define HAMON_PP_CONFIG_MSVC() 0x0004
# define HAMON_PP_CONFIG_MWCC() 0x0008
# define HAMON_PP_CONFIG_BCC() 0x0010
# define HAMON_PP_CONFIG_EDG() 0x0020
# define HAMON_PP_CONFIG_DMC() 0x0040
#
# ifndef HAMON_PP_CONFIG_FLAGS
#    if defined(__GCCXML__)
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_STRICT())
#    elif defined(__WAVE__)
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_STRICT())
#    elif defined(__MWERKS__) && __MWERKS__ >= 0x3200
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_STRICT())
#    elif defined(__EDG__) || defined(__EDG_VERSION__)
#        if defined(_MSC_VER) && (defined(__INTELLISENSE__) || __EDG_VERSION__ >= 308)
#            define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_MSVC())
#        else
#            define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_EDG() | HAMON_PP_CONFIG_STRICT())
#        endif
#    elif defined(__MWERKS__)
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_MWCC())
#    elif defined(__DMC__)
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_DMC())
#    elif defined(__BORLANDC__) && __BORLANDC__ >= 0x581
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_STRICT())
#    elif defined(__BORLANDC__) || defined(__IBMC__) || defined(__IBMCPP__) || defined(__SUNPRO_CC)
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_BCC())
#    elif defined(_MSC_VER) && !defined(__clang__)
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_MSVC())
#    else
#        define HAMON_PP_CONFIG_FLAGS() (HAMON_PP_CONFIG_STRICT())
#    endif
# endif
#
# /* HAMON_PP_CONFIG_EXTENDED_LINE_INFO */
#
# ifndef HAMON_PP_CONFIG_EXTENDED_LINE_INFO
#    define HAMON_PP_CONFIG_EXTENDED_LINE_INFO 0
# endif
#
# /* HAMON_PP_CONFIG_ERRORS */
#
# ifndef HAMON_PP_CONFIG_ERRORS
#    ifdef NDEBUG
#        define HAMON_PP_CONFIG_ERRORS 0
#    else
#        define HAMON_PP_CONFIG_ERRORS 1
#    endif
# endif
#
# /* HAMON_PP_VARIADICS */
#
# define HAMON_PP_VARIADICS_MSVC 0
# if !defined HAMON_PP_VARIADICS
#    /* variadic support explicitly disabled for all untested compilers */
#    if defined __GCCXML__ || defined __CUDACC__ || defined __PATHSCALE__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || ( defined __SUNPRO_CC && __SUNPRO_CC < 0x5120 ) || defined __HP_aCC && !defined __EDG__ || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI
#        define HAMON_PP_VARIADICS 0
#    /* VC++ (C/C++) */
#    elif defined _MSC_VER && _MSC_VER >= 1400 && (!defined __EDG__ || defined(__INTELLISENSE__)) && !defined __clang__
#        define HAMON_PP_VARIADICS 1
#        undef HAMON_PP_VARIADICS_MSVC
#        define HAMON_PP_VARIADICS_MSVC 1
#    /* Wave (C/C++), GCC (C++) */
#    elif defined __WAVE__ && __WAVE_HAS_VARIADICS__ || defined __GNUC__ && defined __GXX_EXPERIMENTAL_CXX0X__ && __GXX_EXPERIMENTAL_CXX0X__
#        define HAMON_PP_VARIADICS 1
#    /* EDG-based (C/C++), GCC (C), and unknown (C/C++) */
#    elif !defined __cplusplus && __STDC_VERSION__ >= 199901L || __cplusplus >= 201103L
#        define HAMON_PP_VARIADICS 1
#    else
#        define HAMON_PP_VARIADICS 0
#    endif
# elif !HAMON_PP_VARIADICS + 1 < 2
#    undef HAMON_PP_VARIADICS
#    define HAMON_PP_VARIADICS 1
#    if defined _MSC_VER && _MSC_VER >= 1400 && (defined(__INTELLISENSE__) || !(defined __EDG__ || defined __GCCXML__ || defined __CUDACC__ || defined __PATHSCALE__ || defined __clang__ || defined __DMC__ || defined __CODEGEARC__ || defined __BORLANDC__ || defined __MWERKS__ || defined __SUNPRO_CC || defined __HP_aCC || defined __MRC__ || defined __SC__ || defined __IBMCPP__ || defined __PGI))
#        undef HAMON_PP_VARIADICS_MSVC
#        define HAMON_PP_VARIADICS_MSVC 1
#    endif
# else
#    undef HAMON_PP_VARIADICS
#    define HAMON_PP_VARIADICS 0
# endif
#
#endif // HAMON_PREPROCESSOR_CONFIG_CONFIG_HPP
