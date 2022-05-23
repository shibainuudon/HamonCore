/**
 *	@file	seq.hpp
 *
 *	@brief
 */

#ifndef HAMON_PREPROCESSOR_SEQ_SEQ_HPP
#define HAMON_PREPROCESSOR_SEQ_SEQ_HPP
#
# include <hamon/preprocessor/config/config.hpp>
# include <hamon/preprocessor/seq/elem.hpp>
#
# /* HAMON_PP_SEQ_HEAD */
#
# define HAMON_PP_SEQ_HEAD(seq) HAMON_PP_SEQ_ELEM(0, seq)
#
# /* HAMON_PP_SEQ_TAIL */
#
# if HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MWCC()
#    define HAMON_PP_SEQ_TAIL(seq) HAMON_PP_SEQ_TAIL_1((seq))
#    define HAMON_PP_SEQ_TAIL_1(par) HAMON_PP_SEQ_TAIL_2 ## par
#    define HAMON_PP_SEQ_TAIL_2(seq) HAMON_PP_SEQ_TAIL_I ## seq
# elif HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_MSVC()
#    define HAMON_PP_SEQ_TAIL(seq) HAMON_PP_SEQ_TAIL_ID(HAMON_PP_SEQ_TAIL_I seq)
#    define HAMON_PP_SEQ_TAIL_ID(id) id
# elif HAMON_PP_CONFIG_FLAGS() & HAMON_PP_CONFIG_EDG()
#    define HAMON_PP_SEQ_TAIL(seq) HAMON_PP_SEQ_TAIL_D(seq)
#    define HAMON_PP_SEQ_TAIL_D(seq) HAMON_PP_SEQ_TAIL_I seq
# else
#    define HAMON_PP_SEQ_TAIL(seq) HAMON_PP_SEQ_TAIL_I seq
# endif
#
# define HAMON_PP_SEQ_TAIL_I(x)
#
# /* HAMON_PP_SEQ_NIL */
#
# define HAMON_PP_SEQ_NIL(x) (x)
#
#endif // HAMON_PREPROCESSOR_SEQ_SEQ_HPP
