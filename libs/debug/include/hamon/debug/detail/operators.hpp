/**
 *	@file	operators.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_OPERATORS_HPP
#define HAMON_DEBUG_DETAIL_OPERATORS_HPP

#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace debug
{

namespace detail
{

namespace op
{

#define HAMON_ASSERT_DETAIL_FOR_EACH_CONST_OP(action)\
	action(->*, MEMP)                 \
	action(* , MUL)                   \
	action(/ , DIV)                   \
	action(% , MOD)                   \
	action(+ , ADD)                   \
	action(- , SUB)                   \
	action(<<, LSH)                   \
	action(>>, RSH)                   \
	action(< , LT)                    \
	action(<=, LE)                    \
	action(> , GT)                    \
	action(>=, GE)                    \
	action(==, EQ)                    \
	action(!=, NE)                    \
	action(&& , AND)                  \
	action(|| , OR)                   \
	action(& , BAND)                  \
	action(^ , XOR)                   \
	action(| , BOR)                   \
/**/


#define HAMON_ASSERT_DETAIL_DEFINE_CONST_OPER(oper, name)				\
template <typename Lhs, typename Rhs>				\
struct name											\
{													\
    using optype = decltype(hamon::declval<Lhs>() oper hamon::declval<Rhs>());	\
    using result_type = hamon::remove_reference_t<optype>;	\
                                                    \
    static result_type                              \
    eval(Lhs const& lhs, Rhs const& rhs)			\
    {                                               \
        return lhs oper rhs;                        \
    }                                               \
													\
	static char const* label(void)					\
	{												\
		return #oper;								\
	}												\
};                                                  \
/**/

HAMON_ASSERT_DETAIL_FOR_EACH_CONST_OP(HAMON_ASSERT_DETAIL_DEFINE_CONST_OPER)

#undef HAMON_ASSERT_DETAIL_DEFINE_CONST_OPER

}	// namespace op

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_OPERATORS_HPP
