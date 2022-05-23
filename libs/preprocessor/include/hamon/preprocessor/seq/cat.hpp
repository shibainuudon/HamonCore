/**
 *	@file	cat.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_SEQ_CAT_HPP
#define HAMON_PREPROCESSOR_SEQ_CAT_HPP
#
# include <hamon/preprocessor/arithmetic/dec.hpp>
# include <hamon/preprocessor/config/config.hpp>
# include <hamon/preprocessor/control/if.hpp>
# include <hamon/preprocessor/seq/fold_left.hpp>
# include <hamon/preprocessor/seq/seq.hpp>
# include <hamon/preprocessor/seq/size.hpp>
# include <hamon/preprocessor/tuple/eat.hpp>
#
# /* HAMON_PP_SEQ_CAT */
#
# define HAMON_PP_SEQ_CAT(seq)                \
    HAMON_PP_IF(                              \
        HAMON_PP_DEC(HAMON_PP_SEQ_SIZE(seq)), \
        HAMON_PP_SEQ_CAT_I,                   \
        HAMON_PP_SEQ_HEAD                     \
    )(seq)                                    \
    /**/
# define HAMON_PP_SEQ_CAT_I(seq) HAMON_PP_SEQ_FOLD_LEFT(HAMON_PP_SEQ_CAT_O, HAMON_PP_SEQ_HEAD(seq), HAMON_PP_SEQ_TAIL(seq))
#
# define HAMON_PP_SEQ_CAT_O(s, st, elem) HAMON_PP_SEQ_CAT_O_I(st, elem)
# define HAMON_PP_SEQ_CAT_O_I(a, b) a ## b
#
# /* HAMON_PP_SEQ_CAT_S */
#
# define HAMON_PP_SEQ_CAT_S(s, seq)           \
    HAMON_PP_IF(                              \
        HAMON_PP_DEC(HAMON_PP_SEQ_SIZE(seq)), \
        HAMON_PP_SEQ_CAT_S_I_A,               \
        HAMON_PP_SEQ_CAT_S_I_B                \
    )(s, seq)                                 \
    /**/
# define HAMON_PP_SEQ_CAT_S_I_A(s, seq) HAMON_PP_SEQ_FOLD_LEFT_ ## s(HAMON_PP_SEQ_CAT_O, HAMON_PP_SEQ_HEAD(seq), HAMON_PP_SEQ_TAIL(seq))
# define HAMON_PP_SEQ_CAT_S_I_B(s, seq) HAMON_PP_SEQ_HEAD(seq)
#
#endif // HAMON_PREPROCESSOR_SEQ_CAT_HPP
