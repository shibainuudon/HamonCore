/**
 *	@file	declval.hpp
 *
 *	@brief	declval を定義
 */

#ifndef HAMON_UTILITY_DECLVAL_HPP
#define HAMON_UTILITY_DECLVAL_HPP

#include <hamon/type_traits/add_rvalue_reference.hpp>

namespace hamon
{

// 22.2.6 Function template declval[declval]

template <typename T>
hamon::add_rvalue_reference_t<T> declval() noexcept;

}	// namespace hamon

#endif // HAMON_UTILITY_DECLVAL_HPP
