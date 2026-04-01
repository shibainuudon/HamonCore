/**
 *	@file	vector_value_t.hpp
 *
 *	@brief	vector_value_t の定義
 */

#ifndef HAMON_BIGINT_BIGINT_ALGO_DETAIL_VECTOR_VALUE_T_HPP
#define HAMON_BIGINT_BIGINT_ALGO_DETAIL_VECTOR_VALUE_T_HPP

#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{
namespace bigint_algo
{
namespace detail
{

template <typename VectorType>
using vector_value_t = hamon::remove_cvref_t<decltype(*hamon::declval<VectorType&>().data())>;

}	// namespace detail
}	// namespace bigint_algo
}	// namespace hamon

#endif // HAMON_BIGINT_BIGINT_ALGO_DETAIL_VECTOR_VALUE_T_HPP
