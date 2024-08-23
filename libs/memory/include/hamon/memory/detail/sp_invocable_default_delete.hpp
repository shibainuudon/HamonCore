/**
 *	@file	sp_invocable_default_delete.hpp
 *
 *	@brief	sp_invocable_default_delete を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SP_INVOCABLE_DEFAULT_DELETE_HPP
#define HAMON_MEMORY_DETAIL_SP_INVOCABLE_DEFAULT_DELETE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [util.smartptr.shared.const]/3
// When T is an array type, the expression delete[] p is well-formed.
// When T is not an array type, the expression delete p is well-formed.

#if (defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) || defined(HAMON_GCC_VERSION)

// Visual Studio 2019 までだと内部コンパイラエラーになってしまう
// 
// gcc では operator delete でのSFINAEはうまく働かない
// (libcxxのshared_ptr.hのコメントより)

template <typename T, typename Y>
using sp_invocable_default_delete = hamon::true_type;

#else

template <typename Y, typename = void>
struct sp_invocable_default_delete_impl
	: public hamon::false_type {};

template <typename Y>
struct sp_invocable_default_delete_impl<Y, hamon::void_t<decltype(delete hamon::declval<Y*>())>>
	: public hamon::true_type {};

template <typename Y, typename = void>
struct sp_invocable_default_delete_array_impl
	: public hamon::false_type {};

template <typename Y>
struct sp_invocable_default_delete_array_impl<Y, hamon::void_t<decltype(delete[] hamon::declval<Y*>())>>
	: public hamon::true_type {};

template <typename T, typename Y>
using sp_invocable_default_delete =
	hamon::conditional_t<
		hamon::is_array<T>::value,
		sp_invocable_default_delete_array_impl<Y>,
		sp_invocable_default_delete_impl<Y>
	>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SP_INVOCABLE_DEFAULT_DELETE_HPP
