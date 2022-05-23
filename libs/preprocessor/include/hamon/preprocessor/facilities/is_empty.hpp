/**
 *	@file	is_empty.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#define HAMON_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#
# include <hamon/preprocessor/config/config.hpp>
#
# if HAMON_PP_VARIADICS
#
# include <hamon/preprocessor/facilities/is_empty_variadic.hpp>
#
# else
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC() && ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
# include <hamon/preprocessor/tuple/elem.hpp>
# include <hamon/preprocessor/facilities/identity.hpp>
# else
# include <hamon/preprocessor/cat.hpp>
# include <hamon/preprocessor/detail/split.hpp>
# endif
#
# /* HAMON_PP_IS_EMPTY */
#
# if ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC() && ~HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
#    define HAMON_PP_IS_EMPTY(x) HAMON_PP_IS_EMPTY_I(x HAMON_PP_IS_EMPTY_HELPER)
#    define HAMON_PP_IS_EMPTY_I(contents) HAMON_PP_TUPLE_ELEM(2, 1, (HAMON_PP_IS_EMPTY_DEF_ ## contents()))
#    define HAMON_PP_IS_EMPTY_DEF_HAMON_PP_IS_EMPTY_HELPER 1, HAMON_PP_IDENTITY(1)
#    define HAMON_PP_IS_EMPTY_HELPER() , 0
# else
#    if HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC()
#        define HAMON_PP_IS_EMPTY(x) HAMON_PP_IS_EMPTY_I(HAMON_PP_IS_EMPTY_HELPER x ())
#        define HAMON_PP_IS_EMPTY_I(test) HAMON_PP_IS_EMPTY_II(HAMON_PP_SPLIT(0, HAMON_PP_CAT(HAMON_PP_IS_EMPTY_DEF_, test)))
#        define HAMON_PP_IS_EMPTY_II(id) id
#    else
#        define HAMON_PP_IS_EMPTY(x) HAMON_PP_IS_EMPTY_I((HAMON_PP_IS_EMPTY_HELPER x ()))
#        define HAMON_PP_IS_EMPTY_I(par) HAMON_PP_IS_EMPTY_II ## par
#        define HAMON_PP_IS_EMPTY_II(test) HAMON_PP_SPLIT(0, HAMON_PP_CAT(HAMON_PP_IS_EMPTY_DEF_, test))
#    endif
#    define HAMON_PP_IS_EMPTY_HELPER() 1
#    define HAMON_PP_IS_EMPTY_DEF_1 1, HAMON_PP_NIL
#    define HAMON_PP_IS_EMPTY_DEF_HAMON_PP_IS_EMPTY_HELPER 0, HAMON_PP_NIL
# endif
#
# endif /* HAMON_PP_VARIADICS */
#
#endif // HAMON_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
