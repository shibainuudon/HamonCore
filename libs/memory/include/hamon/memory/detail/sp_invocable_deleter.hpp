/**
 *	@file	sp_invocable_deleter.hpp
 *
 *	@brief	sp_invocable_deleter を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SP_INVOCABLE_DELETER_HPP
#define HAMON_MEMORY_DETAIL_SP_INVOCABLE_DELETER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

// [util.smartptr.shared.const]/9
// d(p) is a well-formed expression.
template <typename D, typename Y, typename = void>
struct sp_invocable_deleter
	: public hamon::false_type {};

template <typename D, typename Y>
struct sp_invocable_deleter<D, Y, hamon::void_t<decltype(hamon::declval<D&>()(hamon::declval<Y&>()))>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SP_INVOCABLE_DELETER_HPP
