/**
 *	@file	expression_base.hpp
 *
 *	@brief
 */

#ifndef HAMON_DEBUG_DETAIL_EXPRESSION_BASE_HPP
#define HAMON_DEBUG_DETAIL_EXPRESSION_BASE_HPP

#include <hamon/debug/detail/binary_expression_fwd.hpp>
#include <hamon/debug/detail/value_expression_fwd.hpp>
#include <hamon/debug/detail/operators.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace debug
{

namespace detail
{

template <typename ExprType, typename ValType>
class expression_base
{
public:

#define HAMON_ASSERT_DETAIL_ADD_OP_SUPPORT(oper, name)	\
    template <typename T> HAMON_CONSTEXPR	\
    binary_expression<ExprType, value_expression<T>, op::name<ValType, hamon::remove_reference_t<T>>>  \
    operator oper(T&& rhs) const                                 \
    {                                                           \
        return binary_expression<ExprType, value_expression<T>, op::name<ValType, hamon::remove_reference_t<T>>> \
            (hamon::forward<ExprType const>(*static_cast<ExprType const*>(this)),                \
              value_expression<T>(hamon::forward<T>(rhs)));                           \
    }                                                           \
/**/

	HAMON_ASSERT_DETAIL_FOR_EACH_CONST_OP(HAMON_ASSERT_DETAIL_ADD_OP_SUPPORT)

#undef HAMON_ASSERT_DETAIL_ADD_OP_SUPPORT
};

}	// namespace detail

}	// namespace debug

}	// namespace hamon

#endif // HAMON_DEBUG_DETAIL_EXPRESSION_BASE_HPP
